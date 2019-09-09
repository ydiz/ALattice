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

class LeapFrog : public Integrator {
  public:
    using Integrator::Integrator;

    std::string name() const override;
    void do_integrate(GaugeField &U) override;
};
