import cv2

def main():
    cam_index = 0   # /dev/video0

    cap = cv2.VideoCapture(cam_index)

    if not cap.isOpened():
        print(" Failed to open camera")
        return

    ret, frame = cap.read()
    if not ret:
        print(" Failed to capture frame")
        return

    output_file = "test_frame.jpg"
    cv2.imwrite(output_file, frame)
    print(f" Frame captured and saved to {output_file}")

    cap.release()

if __name__ == "__main__":
    main()