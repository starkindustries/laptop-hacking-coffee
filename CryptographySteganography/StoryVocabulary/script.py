#!/bin/python3
# Story Vocabulary

from PIL import Image

image_file = 'story_vocabulary_subsection.png'
im = Image.open(image_file)
pixels = im.load()
imageSize = im.size
# print(f"Image size: {imageSize}")

print("[x,y]: r g b")
print("------------")

for x in range(0, imageSize[0], 2):
    for y in range(imageSize[1]):
        color = pixels[x, y]
        red = "2" if color[0] else " "
        green = "2" if color[1] else " "
        blue = "2" if color[2] else " "
        print(f"[{x},{y}]: {red} {green} {blue}")
    print("")

# IMAGINE ONE PIXEL BUT THREE
# LHC{IMAGINE ONE PIXEL BUT THREE}