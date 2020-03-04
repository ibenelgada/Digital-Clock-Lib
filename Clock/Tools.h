#ifndef TOOLS_H
#define TOOLS_H

String numberToFixedString(int number, int len){
  String str = String(number);

  while(str.length() < len){
    str = "0" + str;
  }
  return str;
}

#endif
