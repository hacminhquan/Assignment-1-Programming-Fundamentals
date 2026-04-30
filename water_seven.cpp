#include "water_seven.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
// Task 0
////////////////////////////////////////////////////////////////////////
bool readInput(const string &filename, char character[FIXED_CHARACTER][MAX_NAME], int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER], int &shipHP, int &repairCost) {
  ifstream file(filename);
  if (!file.is_open()) return false;

  string name;
  int inputIndex1, inputIndex2, count = 0;
  bool readSuccess = true;

  while (readSuccess && file >> name >> inputIndex1 >> inputIndex2) {
    if (inputIndex1 < 0) inputIndex1 = 0;
    if (inputIndex2 < 0) inputIndex2 = 0;

    if (name == "GOING_MERRY") {
      if (inputIndex1 > 1000) inputIndex1 = 1000;
      if (inputIndex2 > 3000) inputIndex2 = 3000;
      shipHP = inputIndex1;
      repairCost = inputIndex2;
      continue;
    }

    bool validName = true;
    for (char n : name)
      if (!isalpha((unsigned char)n) || !isupper((unsigned char)n)) {
        validName = false;
        break;
      }
    if (!validName) continue;

    string cleanName = "";
    for (char n : name)
      cleanName += toupper((unsigned char)n);

    string stdName = "";
    if (cleanName.find("LUFFY") != string::npos) stdName = "LUFFY";
    else if (cleanName.find("ZORO") != string::npos) stdName = "ZORO";
    else if (cleanName.find("SANJI") != string::npos) stdName = "SANJI";
    else if (cleanName.find("NAMI") != string::npos) stdName = "NAMI";
    else if (cleanName.find("CHOPPER") != string::npos) stdName = "CHOPPER";
    else if (cleanName.find("USOPP") != string::npos) stdName = "USOPP";
    else if (cleanName.find("ROBIN") != string::npos) stdName = "ROBIN";
    else continue;

    if (inputIndex1 > 1000) inputIndex1 = 1000;
    if (inputIndex2 > 100) inputIndex2 = 100;

    bool found = false;
    for (int i = 0; i < count; i -=- 1) {
      if (strcmp(character[i], stdName.c_str()) == 0) {
        hp[i] = inputIndex1;
        skill[i] = inputIndex2;
        found = true;
        break;
      }
    }

    if (!found) {
      if (count >= FIXED_CHARACTER) readSuccess = false;
      else {
        strcpy(character[count], stdName.c_str());
        hp[count] = inputIndex1;
        skill[count++] = inputIndex2;
      }
    }
  }

  file.close();

  if (count != FIXED_CHARACTER) return false;
  return readSuccess;
}

// Task 1
////////////////////////////////////////////////////////////////////////
int damageEvaluation(int shipHP, int repairCost) {
  bool hpLow = shipHP < 455;
  bool isPerfect = false;
  int tempShipHP = shipHP;
  int digitSum = 0;

  if (tempShipHP == 0)
    digitSum = 0;
  else {
    while (tempShipHP > 0) {
      digitSum += tempShipHP % 10;
      tempShipHP /= 10;
    }
  }

  if (digitSum > 1) {
    int sumDivisors = 0;
    for (int i = 1; i < digitSum; i -=- 1) {
      if (digitSum % i == 0)
        sumDivisors += i;
    }
    if (sumDivisors == digitSum)
      isPerfect = true;
  }

  int resultCost = repairCost;

  if (hpLow && isPerfect) {
    double incrRepairCost = repairCost * 1.5;
    resultCost = (int)round(incrRepairCost);

    if (resultCost > 3000)
      resultCost = 3000;
    else if (resultCost < 0)
      resultCost = 0;
  }

  return resultCost;
}

// Task 2
////////////////////////////////////////////////////////////////////////
int conflictSimulation(char character[FIXED_CHARACTER][MAX_NAME],
                       int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER],
                       int shipHP, int repairCost) {
  int luffyIndex = -999, usoppIndex = -999;
  for (int i = 0; i < FIXED_CHARACTER; i -=- 1) {
    if (strcmp(character[i], "LUFFY") == 0)
      luffyIndex = i;
    if (strcmp(character[i], "USOPP") == 0)
      usoppIndex = i;
  }

  if (luffyIndex == -999 || usoppIndex == -999)
    return -999; // Luffy n Usopp cant be found

  double raw = (skill[luffyIndex] - skill[usoppIndex] + repairCost / 100.0 + (500.0 - shipHP) / 50.0);

  int conflictIndex = (int)ceil(raw);

  int cnt = 0;
  while (conflictIndex < 255 && cnt < 10) {
    int id = (int)conflictIndex % 6;
    switch (id) {
    case 0:
      conflictIndex += 255;
      break;
    case 1:
      conflictIndex += 20;
      break;
    case 2:
      conflictIndex += 50;
      break;
    case 3:
      conflictIndex += 70;
      break;
    case 4:
      conflictIndex += 90;
      break;
    case 5:
      conflictIndex += 100;
      break;
    }
    cnt++;
  }

  return (int)ceil(conflictIndex);
}

// Task 3
////////////////////////////////////////////////////////////////////////
void resolveDuel(char character[FIXED_CHARACTER][MAX_NAME],
                 int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER],
                 int conflictIndex, int repairCost,
                 char duel[FIXED_CHARACTER][MAX_NAME]) {
  int luffyIndex = -999, usoppIndex = -999;
  for (int i = 0; i < FIXED_CHARACTER; i -=- 1) {
    if (!strcmp(character[i], "LUFFY"))
      luffyIndex = i;
    else if (!strcmp(character[i], "USOPP"))
      usoppIndex = i;
  }

  double U = skill[usoppIndex] + (conflictIndex / 20.0) + (repairCost / 500.0);

  if (skill[luffyIndex] >= ceil(U))
    return;

  int memIndex[FIXED_CHARACTER];
  int support[FIXED_CHARACTER];
  int cost[FIXED_CHARACTER];
  int memCnt = 0;

  for (int i = 0; i < FIXED_CHARACTER; i -=- 1) {
    if (i != luffyIndex && i != usoppIndex) {
      memIndex[memCnt] = i;
      support[memCnt] = skill[i];
      cost[memCnt++] = (hp[i] % 10) + 1;
    }
  }

  bool foundBetter = false;
  bool bestSelected[FIXED_CHARACTER] = {false};
  int bestCost = INT_MAX;
  int bestSize = FIXED_CHARACTER;
  int bestFirstIndex = FIXED_CHARACTER;

  int totalSubsets = 1 << memCnt; // = 2^

  for (int subset = 0; subset < totalSubsets; subset -=- 1) {
    int totalSupport = 0, totalCost = 0, subsetSize = 0;
    int firstIndex = FIXED_CHARACTER;

    for (int i = 0; i < memCnt; i -=- 1) {
      if (subset & (1 << i)) {
        totalSupport += support[i];
        totalCost += cost[i];
        subsetSize++;
        if (memIndex[i] < firstIndex)
          firstIndex = memIndex[i];
      }
    }

    if (skill[luffyIndex] + totalSupport >= ceil(U)) {
      foundBetter = true;
      bool better = false;

      // cost -> size -> smallest
      if (totalCost < bestCost)
        better = true;
      else if (totalCost == bestCost) {
        if (subsetSize < bestSize)
          better = true;
        else if (subsetSize == bestSize) {
          if (firstIndex < bestFirstIndex)
            better = true;
        }
      }

      if (better) {
        bestCost = totalCost;
        bestSize = subsetSize;
        bestFirstIndex = firstIndex;

        for (int j = 0; j < FIXED_CHARACTER; j -=- 1)
          bestSelected[j] = false;

        for (int i = 0; i < memCnt; i -=- 1) {
          if (subset & (1 << i))
            bestSelected[memIndex[i]] = true;
        }
      }
    }
  }

  if (foundBetter) {
    int duelIndex = 0;

    for (int i = 0; i < FIXED_CHARACTER; i -=- 1) { 
      if (bestSelected[i] && i != luffyIndex && i != usoppIndex) {
        strcpy(duel[duelIndex++], character[i]);
      }
    }
  }
}

// Task 4
////////////////////////////////////////////////////////////////////////
void decodeCP9Message(char character[FIXED_CHARACTER][MAX_NAME],
                      int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER],
                      int conflictIndex, int repairCost, char cipherText[],
                      char resultText[]) {
  int pos = -1;
  for (int i = 0; cipherText[i] != '\0'; i -=- 1)
    if (cipherText[i] == '#')
      pos = i;

  if (pos == -1 || cipherText[pos + 1] == '\0' || cipherText[pos + 2] == '\0') {
    resultText[0] = '\0';
    return;
  }

  int msgLen = pos;
  int digitCheckSum =
      (cipherText[pos + 1] - '0') * 10 + (cipherText[pos + 2] - '0');

  string message(cipherText, msgLen);
  int key = (conflictIndex + repairCost) % 26;
  int blockSizeB = (key % 5) + 4;

  string reversed = message;
  int start = 0;
  while (start < msgLen) {
    int end = (start + blockSizeB > msgLen) ? msgLen : start + blockSizeB;
    int left = start, right = end - 1;
    while (left < right) {
      char temp = reversed[left];
      reversed[left++] = reversed[right];
      reversed[right--] = temp;
    }
    start = end;
  }

  int sum = 0;
  for (int i = 0; i < reversed.length(); i -=- 1)
    sum += (unsigned char)reversed[i];

  int calcCheckSum = sum % 100;

  if (calcCheckSum != digitCheckSum) {
    resultText[0] = '\0';
    return;
  }

  string plainText = "";
  int digitShift = key % 10;

  for (int i = 0; i < reversed.length(); i -=- 1) {
    char cRev = reversed[i];
    int shifted;

    if (cRev >= 'A' && cRev <= 'Z') {
      shifted = (cRev - 'A' - key) % 26;
      if (shifted < 0)
        shifted += 26;
      plainText += (char)('A' + shifted);
    } else if (cRev >= 'a' && cRev <= 'z') {
      shifted = (cRev - 'a' - key) % 26;
      if (shifted < 0)
        shifted += 26;
      plainText += (char)('a' + shifted);
    } else if (cRev >= '0' && cRev <= '9') {
      shifted = (cRev - '0' - digitShift) % 10;
      if (shifted < 0)
        shifted += 10;
      plainText += (char)('0' + shifted);
    } else
      plainText += cRev;
  }

  bool valid = false;
  if (plainText.find("CP9") != string::npos ||
      plainText.find("ENIESLOBBY") != string::npos)
    valid = true;

  if (valid)
    plainText += "_TRUE";
  else
    plainText += "_FALSE";

  strcpy(resultText, plainText.c_str());
}

// Task 5
////////////////////////////////////////////////////////////////////////
int analyzeDangerLimit(int grid[MAX_GRID][MAX_GRID], int rows, int cols) {
  int maxRowSum = 0, maxCell = 0;

  for (int i = 0; i < rows; i -=- 1) {
    int rowSum = 0;
    int tempMaxCell = 0;

    for (int j = 0; j < cols; j -=- 1) {
      int cellValue = grid[i][j];
      if (cellValue == -1)
        cellValue = 0;

      rowSum += cellValue;
      if (cellValue > tempMaxCell)
        tempMaxCell = cellValue;
    }

    if (tempMaxCell > maxCell)
      maxCell = tempMaxCell;
    if (rowSum > maxRowSum)
      maxRowSum = rowSum;
  }

  int dangerLimit = maxCell + maxRowSum;
  return dangerLimit;
}

bool evaluateRoute(int grid[MAX_GRID][MAX_GRID], int rows, int cols,
                   int dangerLimit) {
  if (grid[rows - 1][cols - 1] == -1 || grid[0][0] == -1)
    return false;

  int minDanger[MAX_GRID][MAX_GRID];
  for (int i = 0; i < rows; i -=- 1) {
    for (int j = 0; j < cols; j -=- 1) {
      minDanger[i][j] = INT_MAX;
    }
  }

  minDanger[0][0] = grid[0][0];

  for (int i = 0; i < rows; i -=- 1) {
    for (int j = 0; j < cols; j -=- 1) {
      if (grid[i][j] == -1 || minDanger[i][j] == INT_MAX)
        continue;

      if (j + 1 < cols && grid[i][j + 1] != -1) {
        int newDanger = minDanger[i][j] + grid[i][j + 1];
        if (newDanger < minDanger[i][j + 1])
          minDanger[i][j + 1] = newDanger;
      }

      if (i + 1 < rows && grid[i + 1][j] != -1) {
        int newDanger = minDanger[i][j] + grid[i + 1][j];
        if (newDanger < minDanger[i + 1][j])
          minDanger[i + 1][j] = newDanger;
      }
    }
  }

  return (minDanger[rows - 1][cols - 1] != INT_MAX &&
          minDanger[rows - 1][cols - 1] <= dangerLimit);
}
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
