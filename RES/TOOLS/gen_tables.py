import json, os, sys

types_json_file = os.path.join("..", "JSON", "types.json")
bases_json_file = os.path.join("..", "JSON", "bases.json")
prefix_suffix_json_file = os.path.join('..', 'JSON', 'prefix_suffix.json')
output_file = "gen_data.cpp"
header_file = "gen_data.h"
header_guard = "__GEN_DATA_H__"

# Given a field (either a number, string, or a list of some combination of the above),
# expand it into a C++-style array initializer, calling write_field recursively to
# resolve internal lists of lists
def write_field(field, outfile):
    # If the field is a string, wrap it in quotes before writing it
    if isinstance(field, str):
        outfile.write(f'"{field}"')
    # If the field is a dict, expand it term by term and wrap the whole thing in brackets
    elif isinstance(field, dict):
        # If the dictionary contains nothing but dictionaries, then we'll write out the
        # number of entries in the dictionary before we write the data.  The assumption
        # is that the data is being stuffed later into a fixed size array (so we can initialize
        # directly from the static data), and the count is needed to know exactly how
        # many elements are being used.  (And yeah, this code is wrought with potential
        # for exceeding bounds checks down the road, but such is life when you're 
        # writing code for an old platform that's trying not to be too heavy).
        is_sub_dict = True
        for subfield in field:
            if not isinstance(field[subfield], dict):
                is_sub_dict = False
        if is_sub_dict:
            outfile.write(f'{len(field)}, ')
        # Then continue
        outfile.write('{')
        for (subfield_idx, subfield) in enumerate(field):
            write_field(field[subfield], outfile)
            if subfield_idx == len(field) - 1:
                outfile.write('}')
            else:
                outfile.write(', ')
    # If the field is a list, recusrively call write_field to expand each element
    elif isinstance(field, list):
        outfile.write('{')
        for (list_idx, list_item) in enumerate(field):
            write_field(list_item, outfile)
            if list_idx == len(field) - 1:
                outfile.write('}')
            else:
                outfile.write(', ')
    # If the field is a boolean set to True, write 'true' (all lowercase)
    elif field is True:
        outfile.write('true')
    # If the field is a boolean set to False, write 'false' (all lowercase)
    elif field is False:
        outfile.write('false')
    # For other cases (mainly numbers), just write it as-is
    else:
        outfile.write(f'{field}')

# Given a struct type, struct name and a list of items, creates
# an pre-defined C++ array using those items.  Prints to stdout by
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
def print_auto_generated_header(outfile):
    outfile.write('// Auto-generated file - do not edit!\n')

def print_includes(outfile):
    outfile.write('#include "itemstr.h"\n\n')

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

    print_auto_generated_header(out)
    print_includes(out)
    process_item_file(types_json_file, out)
    process_item_file(bases_json_file, out)
    process_item_file(prefix_suffix_json_file, out)

def generate_prototypes(filename, outfile):
    f = open(filename)
    loaded_json = json.load(f)
    for deftype in loaded_json:
        struct_type = loaded_json[deftype]['metadata']['struct_type']
        struct_name = loaded_json[deftype]['metadata']['struct_name']
        outfile.write(f'extern {struct_type} {struct_name}[];\n')

# Create the header file from all of the JSON files
def generate_header_file(outfile=None):
    if outfile != None:
        if os.path.exists(outfile):
            os.remove(outfile)
        out = open(outfile, 'w')
    else:
        out = sys.stdout

    print_auto_generated_header(out)
    out.write(f'#ifndef {header_guard}\n')
    out.write(f'#define {header_guard}\n\n')
    print_includes(out)
    generate_prototypes(types_json_file, out)
    generate_prototypes(bases_json_file, out)
    generate_prototypes(prefix_suffix_json_file, out)
    out.write('\n#endif')

generate_source_file(output_file)
generate_header_file(header_file)
