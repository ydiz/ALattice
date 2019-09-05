#pragma once

class Action {
public:
  virtual double S(const GaugeField &U) const = 0;
  virtual GaugeField deriv(const GaugeField &U) const = 0;

  virtual void describe() const = 0;
};

