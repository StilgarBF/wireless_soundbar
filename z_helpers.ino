//-------------------------------------------------------------------------
// http://www.phanderson.com/arduino/arduino_display.html
//
// This has several useful print routines for the Arduino, worth a look
//-------------------------------------------------------------------------
void printBinary(int v, int num_places) {
  int mask = 0, n;

  for (n = 1; n <= num_places; n++) {
    mask = (mask << 1) | 0x0001;
  }
  v = v & mask;  // truncate v to specified number of places

  while (num_places) {

    if (v & (0x0001 << (num_places - 1))) {
      Serial.print("1");
    }
    else {
      Serial.print("0");
    }

    --num_places;
    if (((num_places % 4) == 0) && (num_places != 0)) {
      Serial.print("_");
    }
  }
  Serial.println("");
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// taken from http://www.geeksforgeeks.org/find-position-of-the-only-set-bit/
// A utility function to check whether n is power of 2 or not. See http://goo.gl/17Arj
int isPowerOfTwo(unsigned n)
{  return n && (! (n & (n-1)) ); }

// Returns position of the only set bit in 'n'
int findPosition(unsigned n)
{
    if (!isPowerOfTwo(n))
        return -1;
 
    unsigned i = 1, pos = 1;
 
    // Iterate through bits of n till we find a set bit
    // i&n will be non-zero only when 'i' and 'n' have a set bit
    // at same position
    while (!(i & n))
    {
        // Unset current bit and set the next bit in 'i'
        i = i << 1;
 
        // increment position
        ++pos;
    }
 
    return pos;
}
//-------------------------------------------------------------------------
