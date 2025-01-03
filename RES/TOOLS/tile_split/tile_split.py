import sys
from PIL import Image

def pixel_compare(source_image, target_image):
    if (source_image.width != target_image.width or source_image.height != target_image.height):
        print("Tiles aren't the same size!")
        return False

    for y in range(source_image.height):
        for x in range(source_image.width):
            if source_image.getpixel((x, y)) != target_image.getpixel((x, y)):
                return False
            
    return True

def compare(image, reference_list):
    if len(reference_list) == 0:
        reference_list.append(image)
        return 0

    # Do a slow pixel compare of the source image to each reference image
    # If a match is found, return the tile index
    for i in range(len(reference_list)):
        result = pixel_compare(image, reference_list[i])
        if result == True:
            # Image was matched
            # print(f"Image was matched to tile {i}")
            return i

    # print(f"This is a new tile!")
    tile_idx = len(reference_list)
    reference_list.append(image)
    return tile_idx

def main():
    if len(sys.argv) < 3:
        print("Usage: tile_split.py <image> <size>")
        sys.exit(0)

    image_to_split = sys.argv[1]
    tile_size = int(sys.argv[2])

    source_image = Image.open(image_to_split) 
    tile_map_tiles = []
    tile_map_data = []

    if source_image.width % tile_size != 0:
        print("Warning: source image isn't an exact multiple of the tile width")
    if source_image.height % tile_size != 0:
        print("Warning: source image isn't an exact multiple of the tile height")

    print(f"The image is {int(source_image.width / tile_size)} x {int(source_image.height / tile_size)} tiles")

    x_tile_count = int(source_image.width / tile_size)
    y_tile_count = int(source_image.height / tile_size)

    for y in range(y_tile_count):
        for x in range(x_tile_count):
            crop_box = (tile_size * x, tile_size * y, (tile_size) * (x + 1), (tile_size) * (y + 1))
            crop_image = source_image.crop(crop_box)
            tile_idx = compare(crop_image, tile_map_tiles)
            tile_map_data.append(tile_idx)

    print(f"A total of {len(tile_map_tiles)} tiles were created")

    # The resulting sprint sheet should be 16 tiles wide, 
    # and as many multiples of 16 tiles high as needed to hold the image
    sheet_height = (int(len(tile_map_tiles) / 256) + 1) * 16

    # Create the blank sheet
    tile_sheet = Image.new('RGB', (16 * tile_size, sheet_height * tile_size), (255, 0, 255))
    # Put the tiles into it, 16 per row
    count = 0
    for tile in tile_map_tiles:
        offset_x = count % 16 * tile_size
        offset_y = int(count / 16) * tile_size
        tile_sheet.paste(tile, (offset_x, offset_y))
        count = count + 1

    tile_sheet.save("sheet.png")

    # Dump the tilemap data into a C-style struct
    tile_map_file = open("towndata.txt", "w")
    tile_map_file.write("unsigned short town_tile_data[")
    tile_map_file.write(f"{x_tile_count * y_tile_count}")
    tile_map_file.write("] = {\n\t")
    for i in range(len(tile_map_data)):
        tile_map_file.write(f"{tile_map_data[i]:>3}")
        if i < len(tile_map_data) - 1:
            tile_map_file.write(", ")
        if i > 0 and i % x_tile_count == (x_tile_count - 1):
            tile_map_file.write("\n\t")
    tile_map_file.write("};\n")
    tile_map_file.close()

if __name__ == "__main__":
    main()
