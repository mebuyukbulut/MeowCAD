#include "IDGen.h"

IDGen::IDGen() :index{}{}
IDGen::IDGen(uint32_t firstID) :index{ firstID }{}

uint32_t IDGen::current_ID(){ return index;   }
uint32_t IDGen::next_ID(){	 return ++index; }
