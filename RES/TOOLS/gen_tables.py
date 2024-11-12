import json, os, sys

types_json_file = os.path.join("..", "JSON", "types.json")
bases_json_file = os.path.join("..", "JSON", "bases.json")
output_file = "gen_data.c"
header_file = "gen_data.h"

# Given a struct type, struct name and a list of items, creates
# an pre-defined C array using those items.  Prints to stdout by
# default, but will output to <outfile> if specified
def print_type_definition(s_type, s_name, items, outfile):
    outfile.write(f"{s_type} {s_name}[] = ")
    outfile.write('{\n')
    for (item_idx, item) in enumerate(items):
        outfile.write("   {")
        for (field_idx, field) in enumerate(items[item]):
            field_val = items[item][field]
            if isinstance(field_val, str):
                outfile.write(f'"{field_val}"')
            else:
                outfile.write(f'{field_val}')
            if field_idx == len(items[item]) - 1:
                outfile.write('}')
            else:
                outfile.write(', ')
        if item_idx == len(items) - 1:
            outfile.write('\n};\n')
        else:
            outfile.write(',\n')
    outfile.write('\n')

def process_item_file(filename, outfile):
    f = open(filename)
    loaded_json = json.load(f)
    for deftype in loaded_json:
        print(f'Processing {deftype}...')
        struct_type = loaded_json[deftype]['metadata']['struct_type']
        struct_name = loaded_json[deftype]['metadata']['struct_name']    
        print_type_definition(struct_type, struct_name, loaded_json[deftype]['items'], outfile)                

def print_header(outfile):
    outfile.write('// Auto-generated file - do not edit!\n')

def generate_file(outfile=None):
    if outfile != None:
        if os.path.exists(output_file):
            os.remove(output_file)
        out = open(outfile, 'w')
    else:
        out = sys.stdout

    print_header(out)
    process_item_file(types_json_file, out)

generate_file(output_file)

