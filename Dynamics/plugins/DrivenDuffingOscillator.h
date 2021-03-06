/*
 * DO NOT EDIT THIS FILE.
 *
 * THIS FILE HAS BEEN AUTOMATICALLY GENERATED.
 * ANY CHANGES MADE TO THE CODE WILL BE LOST.
 *
 * TO MODIFY THE PARAMETER VALUES OR DYNAMICAL
 * EQUATIONS EDIT THE XML FILE (dynamics.xml).
 * 
 */
 
#ifndef DRIVENDUFFINGOSCILLATOR_INCLUDED_
#define DRIVENDUFFINGOSCILLATOR_INCLUDED_

#include "BaseModel.h"
#include "RungeKutta4.h"

#include "DrivenDuffingOscillatorParameterDialog.h"

class DrivenDuffingOscillator : public DynamicalModel
{
  Scalar g;
  Scalar a;
  Scalar b;
  Scalar F;
  Scalar w;
public:
  DrivenDuffingOscillator(Scalar G, Scalar A, Scalar B, Scalar F, Scalar W)
     : g(G), a(A), b(B), F(F), w(W)
  { }

  virtual ~DrivenDuffingOscillator() { }

  virtual Vector exact(const Point& p) const
    {
      return Vector(p[2],w,-g*p[2] + a*p[0] - b*p[0]*p[0]*p[0] + F*cos(p[1]));
    }

private:
  virtual void _setValue(const std::string& name, Scalar value)
    {
      if      (name == "g") g = value;
      else if (name == "a") a = value;
      else if (name == "b") b = value;
      else if (name == "F") F = value;
      else if (name == "w") w = value;
    }
};

class DrivenDuffingOscillatorIntegrator : public Integrator
{
  DrivenDuffingOscillator* dynamics;
  RungeKutta4<DrivenDuffingOscillator>* integrator;
public:
  DrivenDuffingOscillatorIntegrator()
    {
      dynamics = new DrivenDuffingOscillator(.12, 1.0, 10.0, .56, .93);
      double stepSize = 0.01;
      integrator = new RungeKutta4<DrivenDuffingOscillator>(*dynamics, stepSize);
    }

  virtual ~DrivenDuffingOscillatorIntegrator()
    {
      delete dynamics;
      delete integrator;
    }

  inline Vector step(const Point& p)
    {
      return integrator->step(p);
    }

  virtual unsigned int getModelVersion()
    {
      return dynamics->getModelVersion();
    }

  virtual CaveDialog* createParameterDialog(GLMotif::PopupMenu *parent)
    {
      return new DrivenDuffingOscillatorParameterDialog(parent, dynamics);
    }

  virtual Vrui::Point center() const
    {
      return Vrui::Point(0.0, 0.0, 3.14159);
    }
};

#endif
