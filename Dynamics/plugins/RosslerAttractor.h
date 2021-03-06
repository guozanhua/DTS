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
 
#ifndef ROSSLERATTRACTOR_INCLUDED_
#define ROSSLERATTRACTOR_INCLUDED_

#include "BaseModel.h"
#include "RungeKutta4.h"

#include "RosslerAttractorParameterDialog.h"

class RosslerAttractor : public DynamicalModel
{
  Scalar a;
  Scalar b;
  Scalar c;
public:
  RosslerAttractor(Scalar A, Scalar B, Scalar C)
     : a(A), b(B), c(C)
  { }

  virtual ~RosslerAttractor() { }

  virtual Vector exact(const Point& p) const
    {
      return Vector(-p[1]-p[2],p[0]+a*p[1],b+p[2]*(p[0]-c));
    }

private:
  virtual void _setValue(const std::string& name, Scalar value)
    {
      if      (name == "a") a = value;
      else if (name == "b") b = value;
      else if (name == "c") c = value;
    }
};

class RosslerAttractorIntegrator : public Integrator
{
  RosslerAttractor* dynamics;
  RungeKutta4<RosslerAttractor>* integrator;
public:
  RosslerAttractorIntegrator()
    {
      dynamics = new RosslerAttractor(0.2, 0.2, 5.0);
      double stepSize = 0.01;
      integrator = new RungeKutta4<RosslerAttractor>(*dynamics, stepSize);
    }

  virtual ~RosslerAttractorIntegrator()
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
      return new RosslerAttractorParameterDialog(parent, dynamics);
    }

  virtual Vrui::Point center() const
    {
      return Vrui::Point(0.0, 0.0, 15.0);
    }
};

#endif
