#pragma once

class WilsonAction : public Action {
public:
  WilsonAction(double _beta) : beta_(_beta) {}

  double S(const GaugeField &U) const override;
  GaugeField deriv(const GaugeField &U) const override;

  void describe() const override;

private:
  double beta_;
};
