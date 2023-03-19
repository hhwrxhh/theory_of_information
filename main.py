import numpy as np
from scipy.stats import entropy
from PIL import Image


def img_entropy(img, img_path):
    hist, _ = np.histogram(img, bins=256, range=(0, 255), density=True)
    print("Entropy of photo " + img_path + " = " + str(entropy(hist, base=2)))


def img_entropy_relative(img_modif, img_orig, img_path):
    hist, _ = np.histogram(img_modif, bins=256, range=(0, 255), density=True)
    base_hist, _ = np.histogram(img_orig, bins=256, range=(0, 255),
                                density=True)
    relative_entropy = entropy(hist, base=2, qk=base_hist)
    print("Relative Entropy of photo " + img_path + " = " + str(relative_entropy))


def discretization(img, level):
    result = img.resize((img.width // level, img.height // level),
                        resample=Image.LANCZOS)
    img_path = 'image/discretization_step(' + str(level) + ').png'
    result.save(img_path)

    return img_path


def quantization(img, level_quant, level_disc):
    result = img.quantize(level_quant)
    img_path = 'image/quantization_lvl(' + str(level_quant) + ')_discretization_step(' \
               + str(level_disc) + ').png'
    result.save(img_path)

    return img_path


def nearest_restoration(img, level):
    img_restored = img.resize(img.size, resample=Image.NEAREST)
    img_path = 'image/discretization_step(' + str(level) + ')_nearest.png'
    img_restored.save(img_path)

    return img_path


def bilinear_restoration(img, level):
    img_restored = img.resize(img.size, resample=Image.BILINEAR)
    img_path = 'image/discretization_step(' + str(level) + ')_bilinear.png'
    img_restored.save(img_path)

    return img_path


def bicubic_restoration(img, level):
    img_restored = img.resize(img.size, resample=Image.BICUBIC)
    img_path = 'image/discretization_step(' + str(level) + ')_bicubic.png'
    img_restored.save(img_path)

    return img_path


img = Image.open('car.png')
tmp = [8, 16, 64]
path = []

for i in range(2, 9, 2):
    img_path = discretization(img, i)

    for j in tmp:
        if i == 8:
            path_2 = quantization(img, j, 0) # the first one(original)
            # img_entropy(Image.open(path_2), path_2)
            img_entropy_relative(Image.open(path_2), img, path_2)
        else:
            path_1 = quantization(Image.open(img_path), j, i - 2)
            # img_entropy(Image.open(path_1), path_1)
            img_entropy_relative(Image.open(path_1), img, path_1)
    print("____________________________________________")
    print()



# Relative entopies

# for i in range(2, 9, 2):
#     img_path = discretization(img, i)
#     near_path = nearest_restoration(Image.open(img_path), i - 2)
#     bicubic_path = bicubic_restoration(Image.open(img_path), i - 2)
#     bilinear_path = bilinear_restoration(Image.open(img_path), i - 2)
#
#     img_entropy_relative(Image.open(near_path), img, near_path)
#     img_entropy_relative(Image.open(bicubic_path), img, bicubic_path)
#     img_entropy_relative(Image.open(bilinear_path), img, bilinear_path)
#
#     print("____________________________________________")
#     print()


