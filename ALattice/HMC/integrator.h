#pragma once

class Integrator {
  public:
    double trajL;
    int MDsteps;
    std::unique_ptr<Action> action;

    template<typename T>
    Integrator(double _trajL, int _MDsteps, const T &_action);

    void update_P(const GaugeField &U, double eps);
    void update_U(GaugeField &U, double eps) const;
    virtual std::string name() const = 0;
    virtual void describe() const;
    virtual double integrate(GaugeField &U);
    virtual void do_integrate(GaugeField &U) = 0;

  protected:
    GaugeField P;
    double step_size;
};

template<typename T>
Integrator::Integrator(double _trajL, int _MDsteps, const T &_action) {
  trajL = _trajL;
  MDsteps = _MDsteps;
  step_size = trajL / MDsteps;
  action.reset(new T(_action));
}

void Integrator::describe() const {
  std::cout << "Integrator Name: " << name() << std::endl;
  std::cout << "trajL: " << trajL << std::endl;
  std::cout << "MDsteps: " << MDsteps << std::endl;
  std::cout << "Step Size: " << step_size << std::endl;
  action->describe();
}

void Integrator::update_P(const GaugeField &U, double eps) {
  GaugeField force = action->deriv(U);
  P -= eps * force;
}

void Integrator::update_U(GaugeField &U, double eps) const {
  U = Exponentiate(P, eps) * U;
}

double Integrator::integrate(GaugeField &U) {

  gaussian(P);
  P = Complex(0, 1) * P; // P must be anti-hermitian

  double Hp0 = - sum(real(trace(P*P)));
  double S0 = action->S(U);
  double H0 = Hp0 + S0;
  std::cout << "Before trajectory: " << "Hp0: " << Hp0 << " S0: " << S0 << " total H0: " << H0 << std::endl;

  do_integrate(U);

  double Hp = - sum(real(trace(P*P)));
  double S = action->S(U);
  double H = Hp + S;
  std::cout << "After trajectory: " << "Hp: " << Hp << " S: " << S << " total H: " << H << std::endl;

  return H - H0;
}

class LeapFrog : public Integrator {
  public:
    using Integrator::Integrator;

    std::string name() const override;
    void do_integrate(GaugeField &U) override;
};

std::string LeapFrog::name() const {
  return "LeapFrog";
}

void LeapFrog::do_integrate(GaugeField &U) {

  for (int step=0; step < MDsteps; ++step) {  // MD step

    if(step==0) update_P(U, step_size / 2.0);

    this->update_U(U, step_size);

    if(step!=MDsteps-1) this->update_P(U, step_size);
    else this->update_P(U, step_size / 2.0);
  }
}
