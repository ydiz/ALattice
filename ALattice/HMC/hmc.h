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
