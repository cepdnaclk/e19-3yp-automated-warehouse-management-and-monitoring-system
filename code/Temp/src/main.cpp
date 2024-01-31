 if (startX == 1 && startY == 0 && endX == 2 && endY == 1) {
        instructions[0] = 1;
        instructions[1] = 2;
        instructions[2] = 1;
    }
    else if (startX == 1 && startY == 0 && endX == 3 && endY == 0) {
        instructions[0] = 1;
        instructions[1] = 1;
    }
    else if (startX == 1 && startY == 0 && endX == 4 && endY == 1) {
        instructions[0] = 1;
        instructions[1] = 1;
        instructions[2] = 2;
        instructions[3] = 1;
    }
    else if (startX == 1 && startY == 0 && endX == 3 && endY == 2) {
        instructions[0] = 1;
        instructions[1] = 1;
        instructions[2] = 2;
        instructions[3] = 1;
        instructions[4] = 2;
        instructions[5] = 1;
    }else if (startX == 2 && startY == 1 && endX == 1 && endY == 0) {
        instructions[0] = 1;
        instructions[1] = 3;
        instructions[2] = 1;
    }
    else if (startX == 2 && startY == 1 && endX == 3 && endY == 0) {
        instructions[0] = 1;
        instructions[1] = 2;
        instructions[2] = 1;
    }
    else if (startX == 2 && startY == 1 && endX == 4 && endY == 1) {
        instructions[0] = 1;
        instructions[1] = 2;
        instructions[2] = 1;
        instructions[3] = 2;
        instructions[4] = 1;
    }
    else if (startX == 2 && startY == 1 && endX == 3 && endY == 2) {
        instructions[0] = 1;
        instructions[1] = 3;
        instructions[2] = 1;
    }else if (startX == 3 && startY == 0 && endX == 2 && endY == 1) {
        instructions[0] = 1;
        instructions[1] = 3;
        instructions[2] = 1;
    }
    else if (startX == 3 && startY == 0 && endX == 1 && endY == 0) {
        instructions[0] = 1;
        instructions[1] = 1;
    }
    else if (startX == 3 && startY == 0 && endX == 4 && endY == 1) {
        instructions[0] = 1;
        instructions[1] = 2;
        instructions[2] = 1;
    }
    else if (startX == 3 && startY == 0 && endX == 3 && endY == 2) {
        instructions[0] = 1;
        instructions[1] = 2;
        instructions[2] = 1;
        instructions[3] = 2;
        instructions[4] = 1;
    }else  if (startX == 4 && startY == 1 && endX == 2 && endY == 1) {
        instructions[0] = 1;
        instructions[1] = 3;
        instructions[2] = 1;
        instructions[3] = 3;
        instructions[4] = 1;
    }
    else if (startX == 4 && startY == 1 && endX == 3 && endY == 0) {
        instructions[0] = 1;
        instructions[1] = 1;
        instructions[2] = 1;
    }
    else if (startX == 4 && startY == 1 && endX == 1 && endY == 0) {
        instructions[0] = 1;
        instructions[1] = 3;
        instructions[2] = 1;
        instructions[3] = 1;
    }
    else if (startX == 4 && startY == 1 && endX == 3 && endY == 2) {
        instructions[0] = 1;
        instructions[1] = 2;
        instructions[2] = 1;
    }else if (startX == 3 && startY == 2 && endX == 2 && endY == 1) {
        instructions[0] = 1;
        instructions[1] = 2;
        instructions[2] = 1;
    }
    else if (startX == 3 && startY == 2 && endX == 3 && endY == 0) {
        instructions[0] = 1;
        instructions[1] = 3;
        instructions[2] = 1;
        instructions[3] = 3;
        instructions[4] = 1;
    }
    else if (startX == 3 && startY == 2 && endX == 1 && endY == 0) {
        instructions[0] = 1;
        instructions[1] = 3;
        instructions[2] = 1;
        instructions[3] = 3;
        instructions[4] = 1;
        instructions[5] = 1;
    }
    else if (startX == 3 && startY == 2 && endX == 4 && endY == 1) {
        instructions[0] = 1;
        instructions[1] = 3;
        instructions[2] = 1;
    }
    else {
        Serial.println("No instructions available for this scenario.");
    }