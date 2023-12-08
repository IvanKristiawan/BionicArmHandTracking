import cvzone
from cvzone.HandTrackingModule import HandDetector
import cv2
import serial

cap = cv2.VideoCapture(0)
detector = HandDetector(maxHands=1, detectionCon=0.7)
mySerial = serial.Serial("COM3", 9600)

while True:
    success, img = cap.read()
    img = detector.findHands(img)
    lmList, bbox = detector.findPosition(img)
    if lmList:
        fingers = detector.fingersUp()
        print(fingers)
        print(fingers[0])

        flipValThumb = 0
        if (fingers[0] == 0):
            flipValThumb = 1

        flipValIndex = 0
        if (fingers[1] == 0):
            flipValIndex = 1

        flipValMiddle = 0
        if (fingers[2] == 0):
            flipValMiddle = 1

        flipValRing = 0
        if (fingers[3] == 0):
            flipValRing = 1

        flipValPinky = 0
        if (fingers[4] == 0):
            flipValPinky = 1


        input = "$" + str(flipValThumb) + str(flipValIndex) + str(flipValMiddle) + str(flipValRing) + str(flipValPinky)
        mySerial.write(str.encode(input))
    cv2.imshow("Image", img)
    cv2.waitKey(1)
