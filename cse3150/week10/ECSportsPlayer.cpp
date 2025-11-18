#include "ECSportsPlayer.h"

class ECTournament{
	public:
		ECTournament(int month, int mr) : month(month), minRank(mr) {}
		int GetMonth() const { return month; }
		int GetMinRank() const { return minRank; }
	private:
		int month;
		int minRank;
}

// ********************************************
// Generic player
bool ECSportsPlayer :: CanPlay(ECTournament &tr) const
{
  // your code
  if (NegativePlay(tr)){
	return false;
  }
  return PositivePlay(tr);
}

// ********************************************
// Ranked player
ECSportsPlayerRanked :: ECSportsPlayerRanked(int r) : rank(r) 
{
}

class ECSportsPlayerDec : public ECSportsPlayer{
	public:
		ECSportsPlayerRanked(int r);
	private:

}


// ********************************************
// Wildcard player: qualify for any tournament 
ECSportsPlayerWildcard :: ECSportsPlayerWildcard(ECSportsPlayer &playerOrig)  
{
} 

// ********************************************
// Displined player: cannot attend any tournament during the period of probation
ECSportsPlayerDisciplined :: ECSportsPlayerDisciplined(ECSportsPlayer &po, int ms, int me) 
{
}

// ********************************************
// Injured player: cannot attend any tournament during the period of injury(injury occurs at a single month) 
ECSportsPlayerInjured :: ECSportsPlayerInjured(ECSportsPlayer &po, int m) 
{
}


