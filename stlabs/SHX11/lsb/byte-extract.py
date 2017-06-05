#!/usr/bin/env python2.7
from PIL import Image
import numpy as np

# The array will be of type `np.uint8`. For integer computations that exceed
# this range, use `np.asarray(Image.open(...), dtype=int)`.
stego = np.asarray(Image.open('Steganography_original.png'))
extracted = stego & 0b00000001

print (extracted)

target = open("output.png", 'w')
target.write(extracted)


extracted *= (255 / 3)

# Compare result with the one from wikipedia
#pen(filename, 'w')
#wiki_extracted = np.asarray(Image.open('Steganography_recovered.png').convert('RGB'))
#if np.all(wiki_extracted == extracted):
#    print ('All pixels match')
