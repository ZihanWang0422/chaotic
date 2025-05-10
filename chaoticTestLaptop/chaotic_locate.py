# import the necessary packages
from skimage.metrics import structural_similarity as compare_ssim
import imutils
import cv2


def shrink_the_range(src, curr):
    """
    Find where approximately the vehicle is.
    src: empty map
    curr: current capture
    Source:
    https://pyimagesearch.com/2017/06/19/image-difference-with-opencv-and-python/#comment-429138
    """

    # convert the images to grayscale
    grayA = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)
    grayB = cv2.cvtColor(curr, cv2.COLOR_BGR2GRAY)

    # compute the Structural Similarity Index (SSIM) between the two
    # images, ensuring that the difference image is returned
    (score, diff) = compare_ssim(grayA, grayB, full=True)
    diff = (diff * 255).astype("uint8")
    # print("SSIM: {}".format(score))

    # threshold the difference image, followed by finding contours to
    # obtain the regions of the two input images that differ
    thresh = cv2.threshold(diff, 0, 255,
                           cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU)[1]
    cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,
                            cv2.CHAIN_APPROX_SIMPLE)
    cnts = imutils.grab_contours(cnts)

    # # loop over the contours
    for c in cnts:
        #     # compute the bounding box of the contour and then draw the
        #     # bounding box on both input images to represent where the two
        #     # images differ
        vertices = cv2.boxPoints(cv2.minAreaRect(c))
    #     cv2.rectangle(src, (x, y), (x + w, y + h), (0, 0, 255), 2)
    #     cv2.rectangle(curr, (x, y), (x + w, y + h), (0, 0, 255), 2)

    # show the output images
    # uncomment for debug use
    # cv2.imshow("Original", src)
    # cv2.imshow("Modified", curr)
    # cv2.imshow("Diff", diff)
    # cv2.imshow("Thresh", thresh)
    # cv2.waitKey(0)
    return score, vertices
