/***************************************************************************
 *   main.cpp  --  This file is part of beamsyncctl.                       *
 *                                                                         *
 *   Copyright (C) 2019 Imanol-Mikel Barba Sabariego                       *
 *                                                                         *
 *   beamsyncctl is free software: you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published     *
 *   by the Free Software Foundation, either version 3 of the License,     *
 *   or (at your option) any later version.                                *
 *                                                                         *
 *   beamsyncctl is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty           *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.               *
 *   See the GNU General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see http://www.gnu.org/licenses/.   *
 *                                                                         *
 ***************************************************************************/

#include <stdio.h>
#include <string.h>

extern int CGSSetDebugOptions(unsigned int);
extern int CGSGetDebugOptions(unsigned int*);
extern int CGSDeferredUpdates(unsigned int);

typedef enum {
  kCGErrorSuccess = 0,
  kCGErrorFailure = 1000,
  kCGErrorIllegalArgument = 1001,
  kCGErrorInvalidConnection = 1002,
  kCGErrorInvalidContext = 1003,
  kCGErrorCannotComplete = 1004,
  kCGErrorNotImplemented = 1006,
  kCGErrorRangeCheck = 1007,
  kCGErrorTypeCheck = 1008,
  kCGErrorInvalidOperation = 1010,
  kCGErrorNoneAvailable = 1011,
} kCGErrorCode;

typedef enum {
    disableBeamSync = 0,
    automaticBeamSync = 1,
    forcedBeamSyncMode = 2
} beamSyncMode;

void printUsage() {
  printf("\n");
  printf("beamsyncctl - Toggles or prints beam sync status\n");
  printf("  -e\tenable\n");
  printf("  -d\tdisable\n");
  printf("  -p\tprint\n");
}

int main(int argc, char **argv) {
  unsigned int disableBeamSyncFlag = 0x08000000;
  unsigned int mode = automaticBeamSync;
  if(argc < 2) {
    perror("No argument provided\n");
    printUsage();
    return 1;
  }
  unsigned int options = 0;
  int res = CGSGetDebugOptions(&options);
  printf("CGSGetDebugOptions(%p) = 0x%x\n",&options,res);
  printf("options = 0x%x\n",options);
  if(!strncmp(argv[1],"-e",2)) {
    options &= (~disableBeamSyncFlag);
    mode = forcedBeamSyncMode;
  } else if(!strncmp(argv[1],"-d",2)) {
    options |= disableBeamSyncFlag;
    mode = disableBeamSync;
  } else if(!strncmp(argv[1],"-p",2)) {
    // stop program here
    return 0;
  } else {
    perror("Unknown option\n");
    printUsage();
    return 1;
  }
  res = CGSSetDebugOptions(options);
  printf("CGSSetDebugOptions(0x%x) = 0x%x\n",options,res);
  res = CGSDeferredUpdates(mode);
  printf("CGSDeferredUpdates(0x%x) = 0x%x\n",mode,res);
  return 0;
}
