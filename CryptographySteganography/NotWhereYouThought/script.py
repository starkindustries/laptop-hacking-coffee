#!/bin/python3

# Not Where You Though

from PIL import Image

def printPixel(x, y, pixels):
    color = pixels[x, y]
    print(f"[{x}, {y}]: {color}")

# Princess Image
image_file = 'princess.png'
im = Image.open(image_file)
pixels = im.load()
imageSize = im.size
print(f"Image size: {imageSize}")

data = ""
for y in range(imageSize[1]):    
    for x in range(imageSize[0]):
        color = pixels[x, y]
        # Get least significant bit (lsb)
        data += bin(color[0])[-1]
        data += bin(color[1])[-1]
        data += bin(color[2])[-1]

# Convert binary to bytes
n = int(data, 2)
n = n.to_bytes((n.bit_length() + 7) // 8, 'big')

# Print out the bytes
print(n.decode())