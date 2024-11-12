import json, os, sys

types_json_file = os.path.join("..", "JSON", "types.json")
bases_json_file = os.path.join("..", "JSON", "bases.json")
output_file = "gen_data.c"
header_file = "gen_data.h"

# Given a field (either a number, string, or a list of some combination of the above),
# expand it into a C-style array initializer, calling write_field recursively to
# resolve internal lists of lists
def write_field(field, outfile):
    if isinstance(field, str):
        outfile.write(f'"{field}"')
    elif isinstance(field, list):
        outfile.write('{')
        for (list_idx, list_item) in enumerate(field):
            write_field(list_item, outfile)
            if list_idx == len(field) - 1:
                outfile.write('}')
            else:
                outfile.write(', ')
    else:
        outfile.write(f'{field}')

# Given a struct type, struct name and a list of items, creates
# an pre-defined C array using those items.  Prints to stdout by
# default, but will output to <outfile> if specified
def print_type_definition(s_type, s_name, items, outfile):
    outfile.write(f"{s_type} {s_name}[] = ")
    outfile.write('{\n')
    # Go through every item in the 'items' list
    for (item_idx, item) in enumerate(items):
        outfile.write("   {")
        for (field_idx, field) in enumerate(items[item]):
            field_val = items[item][field]
            write_field(field_val, outfile)
            if field_idx == len(items[item]) - 1:
                outfile.write('}')
            else:
                outfile.write(', ')
        if item_idx == len(items) - 1:
            outfile.write('\n};\n')
        else:
            outfile.write(',\n')
    outfile.write('\n')

# Prints a comment block describing the particular structure that's being
# generated
def print_type_comment(metadata, outfile):
    try:
        description = metadata['description']
    except KeyError:
        description = None
    try:
        fields = metadata['fields']
    except KeyError:
        fields = None

    outfile.write(f'// {metadata['struct_type']} {metadata['struct_name']}\n')

    if description != None:
        outfile.write('//\n')
        outfile.write(f'//   {description}\n')
    outfile.write('//\n')
    
    if fields != None:
        outfile.write('//   Fields:\n')
        outfile.write('//   {')
        for (idx, field) in enumerate(fields):
            outfile.write(field)
            if idx == len(fields) - 1:
                outfile.write('}\n')
            else:
                outfile.write(', ')

    outfile.write('//\n')

# Prints a header at the top of an auto-generated file
def print_header(outfile):
    outfile.write('// Auto-generated file - do not edit!\n\n')

# Iterates through a JSON file and extracts the data into a C array initializer block
def process_item_file(filename, outfile):
    f = open(filename)
    loaded_json = json.load(f)
    for deftype in loaded_json:
        print(f'Processing {deftype}...')
        struct_type = loaded_json[deftype]['metadata']['struct_type']
        struct_name = loaded_json[deftype]['metadata']['struct_name']

        print_type_comment(loaded_json[deftype]['metadata'], outfile)
        print_type_definition(struct_type, struct_name, loaded_json[deftype]['items'], outfile)                

# Create the source file from all of the JSON files
def generate_source_file(outfile=None):
    if outfile != None:
        if os.path.exists(output_file):
            os.remove(output_file)
        out = open(outfile, 'w')
    else:
        out = sys.stdout

    print_header(out)
    process_item_file(types_json_file, out)

# Create the header file from all of the JSON files
def generate_header_file(outfile=None):
    pass

generate_source_file(output_file)
generate_header_file(header_file)
