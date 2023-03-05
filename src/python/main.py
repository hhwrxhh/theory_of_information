import numpy as np
import cv2
import matplotlib.pyplot as plt

# Histogram of grayscale image

img = cv2.imread(
    'change_to_your_path.'
)

plt.subplot(1, 2, 1)
plt.title("GrayScale")
plt.imshow(img, cmap="gray")

plt.subplot(1, 2, 2)
hist = cv2.calcHist([img], [0], None, [256], [0, 255])
plt.xlabel("Pixel Intensities")
plt.xlim(0, 255)
plt.ylabel("Frequencies")
plt.plot(hist)
plt.title("Color Histogram")
plt.show()
