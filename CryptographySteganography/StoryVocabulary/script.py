#!/bin/python3

# Story Vocabulary

from PIL import Image

def printPixel(x, y, pixels):
    color = pixels[x, y]
    print(f"[{x}, {y}]: {color}")

# Princess Image
image_file = 'story_vocabulary_subsection.png'
im = Image.open(image_file)
pixels = im.load()
imageSize = im.size
# print(f"Image size: {imageSize}")

data = ""
for y in range(imageSize[1]):    
    for x in range(imageSize[0]):
        color = pixels[x, y]
        # Get the 2nd to last significant bit
        for rgb in range(3):
            # if color is 1 (0b1) or 0 (0b0) the [-2] will grab the 'b' which is a problem
            if color[rgb] < 2:
                data += "0"
            else:
                data += bin(color[rgb])[-2]

# Convert binary to bytes
n = int(data, 2)
n = n.to_bytes((n.bit_length() + 7) // 8, 'big')

# Print out the bytes
print(n.decode('utf-8', 'replace'))

###########################################################
# from PIL import Image

# def printPixel(x, y, pixels):
#     color = pixels[x, y]
#     print(f"[{x}, {y}]: {color}")

# def verifyBounds(rightBound, topBound, botBound, pixels):
#     printPixel(rightBound,  topBound-1, pixels) # top-right - 1y
#     printPixel(rightBound+1,topBound,   pixels) # top-right + 1x
#     printPixel(rightBound,  topBound,   pixels) # top-right (black pixel)
#     printPixel(rightBound,  botBound,   pixels) # bot-right (black pixel)
#     printPixel(rightBound+1,botBound,   pixels) # bot-right + 1x
#     printPixel(rightBound,  botBound+1, pixels) # bot-right + 1y

# def findNearBlackPixels(rightBound, topBound, botBound, pixels):
#     blacks = []
#     black = (0, 0, 0)
#     for y in range(topBound, botBound+1):
#         for x in range(0, rightBound+1):
#             color = pixels[x, y]
#             if color != black:
#                 # print(f"[{x}, {y}]: {color}")
#                 # convert color to binary
#                 # print(bin(color[0]))
#                 blacks.append(color)
#     return blacks

# # Story Vocab image
# image_file = 'story_vocabulary.png'
# im = Image.open(image_file)
# pixels = im.load()
# print(f"Image size: {im.size}")

# # 
# # +------------------------------------------------------------------------+
# # |top-left point: (0,15)                        top-right point: (1226,15)|
# # |bot-left point: (0,18)                        bot-right point: (1226,18)|
# # +------------------------------------------------------------------------+
# # 
# # +-------------------------------------------------------+
# # |top-left point: (0,27)        top-right point: (552,27)|
# # |bot-left point: (0,30)        bot-right point: (552,30)|
# # +-------------------------------------------------------+

# print("verify boundaries of 1st black bar")
# rb1 = 1226  # right boundary
# tb1 = 15    # top boundary
# bb1 = 18    # bottom boundary
# verifyBounds(rb1, tb1, bb1, pixels)
# print("")

# print("verify boundaries of 2nd black bar")
# rb2 = 552   # right boundary
# tb2 = 27    # top boundary
# bb2 = 30    # bottom boundary
# verifyBounds(rb2, tb2, bb2, pixels)
# print("")

# # 1st black bar
# nearBlackPixels = findNearBlackPixels(rb1, tb1, bb1, pixels)
            
# # 2nd black bar
# temp = findNearBlackPixels(rb2, tb2, bb2, pixels)
# nearBlackPixels.append(temp)

# print(nearBlackPixels)
# print("\nBottom Black Bar")

# # bottom black bar
# bottomBarPixels = findNearBlackPixels(1919, 1079-7, 1079, pixels)
# print(bottomBarPixels)

# binaryString = ""
# for color in bottomBarPixels:        
#     for rgb in color:
#         if rgb == 2:
#             binaryString += "1"
#         else:
#             binaryString += "0"
# print(f"\nBinary String:\n{binaryString}")
# print(f"\nBinary len:\n{len(binaryString)}")
