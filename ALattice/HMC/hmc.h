#pragma once

struct HMC_para {
  int start_traj;
  int trajs;
  bool doMetro;
  int noMetroUnitil;
  std::string startingType;

  double trajL;
  int MDsteps;
  std::string integrator;

  HMC_para();
  void describe() const;
};

HMC_para::HMC_para() {
  start_traj = 0;
  trajs = 10;
  // trajs = 1;
  doMetro = true;
  noMetroUnitil = 20;
  startingType = "ColdStart";
  trajL = 1.0;
  MDsteps = 10;
  integrator = "LeapFrog";
}

void HMC_para::describe() const {
  std::cout << "starting trajectory: " << start_traj << std::endl;
  std::cout << "number of trajectories: " << trajs << std::endl;
  std::cout << "do Metropolis: " << std::boolalpha << doMetro << std::endl;
  std::cout << "noMetroUnitil: " << noMetroUnitil << std::endl;
}

class HMC {
public:
  HMC_para para;
  GaugeField U;
  std::unique_ptr<Integrator> integrator;

  
  template<typename T>
  HMC(const T &_action);

  template<typename T>
  HMC(const HMC_para & _para, const T &_action);


  void run();
private:
  void setup();
  void evolve_one_traj(bool doMetro);
  bool metropolis_test(double dH);

  RNG<std::uniform_real_distribution<>> rng;
};

template<typename T>
HMC::HMC(const T &_action) {
  integrator.reset(new LeapFrog{para.trajL, para.MDsteps, _action});
}

template<typename T>
HMC::HMC(const HMC_para & _para, const T &_action) {
  para = _para;
  if(para.integrator == "LeapFrog") integrator.reset(new LeapFrog{para.trajL, para.MDsteps, _action});
  else assert(0);
}

void HMC::setup() {
  if(para.startingType == "ColdStart") U = 1.0;
  else assert(0);

  para.describe();
  integrator->describe();
}

void HMC::run() {
  setup();

  bool doMetro;
  for(int i=para.start_traj; i<para.start_traj + para.trajs; ++i) {
    std::cout << "traj: " << i << std::endl;
    doMetro = (i>=para.noMetroUnitil);
    evolve_one_traj(doMetro);
  }
}



void HMC::evolve_one_traj(bool doMetro) {

  GaugeField Ucopy = U;

  double dH = integrator->integrate(U);

  if(doMetro) {
    bool success = metropolis_test(dH);
    if(!success) U = Ucopy;
  }

  std::cout << "Plaq: " << plaq(U) << std::endl;
  std::cout << "LinkTrace: " << linkTrace(U) << std::endl;
}


bool HMC::metropolis_test(double dH) {
  if(dH <= 0) {
    std::cout << "dH: " << dH << " prob: " << 1 << std::endl;
    std::cout << "[ACCEPTED]" << std::endl;
    return true;
  }

  double rand;
  if(U.grid.Rank()==0) rand = rng();
  U.grid.Bcast(0, rand);

  double prb = std::exp(-dH);

  std::cout << "dH: " << dH << " prob: " << prb << std::endl;

  if(rand < prb) {
    std::cout << "[ACCEPTED]" << std::endl;
    return true;
  }
  else {
    std::cout << "[REJECTED]" << std::endl;
    return false;
  }
}

