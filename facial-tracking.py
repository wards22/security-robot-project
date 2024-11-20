import cv2

# Load the cascade
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

# Captures video from an ip camera, specifically
# the esp32 on the elegoo robot
cap = cv2.VideoCapture('http://192.168.4.1/Test')

while True:
    # Read the frame
    _, img = cap.read()
    # Convert to grayscale
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # Detect the faces
    faces = face_cascade.detectMultiScale(gray, 1.1, 4)
    # Draw the rectangle around each face
    i = 0
    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x, y), (x+w, y+h), (255, 0, 0), 2)
        i = i+1
        cv2.putText(img, 'Intruder!!!', (x-10, y-10),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0,0,255), 2)
        print("Warning, Intruder Alert!")
        print('There are unauthorized personnel on the premises!')
    # Display
    cv2.imshow('img', img)
    # Stop if escape key is pressed
    k = cv2.waitKey(30) & 0xff
    if k==27:
        break
# Release the VideoCapture object
cap.release()
