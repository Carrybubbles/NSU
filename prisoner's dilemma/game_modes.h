#ifndef GAME_MODES
#define GAME_MODES

#include <algorithm>
#include "input_reading.h"
#include "prisoner.h"
#include "strategy.h"
#include "Factory.h"
#include "variables.h"

class Modes  {
public:
    Modes(const Input_reader& _Guser);
    virtual ~Modes();
    std::vector<int>& Get_score();
    std::vector<int > make_step(const int& steps);
    std::vector<int >make_step(const int& steps,  std::vector<Prisoner>& _prisoners);
    virtual void  run_mode() = 0;
protected:
    Input_reader input_user;
};

class TournamentMode final : public Modes {
public:
    TournamentMode(const Input_reader& _Guser);
    ~TournamentMode();
    void run_mode() override;
};

class DetailedMode final : public Modes{
public:
    DetailedMode(const Input_reader& _Guser);
    ~DetailedMode();
    void detailed_game();
    void run_mode() override;
};

class FastMode final : public Modes{
public:
    FastMode(const Input_reader& _Guser);
    ~FastMode();
    void  run_mode() override;
};
#endif // GAME_MODES

