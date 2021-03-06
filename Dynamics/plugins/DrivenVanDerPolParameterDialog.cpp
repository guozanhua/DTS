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
 
#include "DrivenVanDerPolParameterDialog.h"
#include "GLMotif/WidgetFactory.h"
#include "IntegrationStepSize.h"
#include "VruiStreamManip.h"

GLMotif::PopupWindow* DrivenVanDerPolParameterDialog::createDialog()
{
  WidgetFactory factory;
  GLMotif::PopupWindow* parameterDialogPopup=factory.createPopupWindow("ParameterDialogPopup", "DrivenVanDerPol Parameters");

  GLMotif::RowColumn* parameterDialog=factory.createRowColumn("ParameterDialog", 3);
  factory.setLayout(parameterDialog);

  factory.createLabel("BParameterLabel", "b");

  currentBValue=factory.createTextField("CurrentBValue", 10);
  currentBValue->setString("2.");

  bParameterSlider=factory.createSlider("BParameterSlider", 15.0);
  bParameterSlider->setValueRange(0.0, 4.0, .01);
  bParameterSlider->setValue(2.);
  bParameterSlider->getValueChangedCallbacks().add(this, &DrivenVanDerPolParameterDialog::sliderCallback);

  factory.createLabel("AParameterLabel", "A");

  currentAValue=factory.createTextField("CurrentAValue", 10);
  currentAValue->setString("3.0");

  AParameterSlider=factory.createSlider("AParameterSlider", 15.0);
  AParameterSlider->setValueRange(0.0, 6.0, .01);
  AParameterSlider->setValue(3.0);
  AParameterSlider->getValueChangedCallbacks().add(this, &DrivenVanDerPolParameterDialog::sliderCallback);

  factory.createLabel("WParameterLabel", "w");

  currentWValue=factory.createTextField("CurrentWValue", 10);
  currentWValue->setString("1.5");

  wParameterSlider=factory.createSlider("WParameterSlider", 15.0);
  wParameterSlider->setValueRange(0.0, 15.0, .01);
  wParameterSlider->setValue(1.5);
  wParameterSlider->getValueChangedCallbacks().add(this, &DrivenVanDerPolParameterDialog::sliderCallback);


  factory.createLabel("StepSizeLabel", "step size");
  stepSizeValue=factory.createTextField("StepSizeValue", 10);
  double step_size = IntegrationStepSize::instance()->getSavedValue("Driven Van Der Pol");
  if (step_size > 0.0) stepSizeValue->setString(toString(step_size).c_str());
  else stepSizeValue->setString("0.01");
  stepSizeSlider=factory.createSlider("StepSizeSlider", 15.0);
  stepSizeSlider->setValueRange(0.0001, 0.05, 0.0001);
  if (step_size > 0.0) stepSizeSlider->setValue(step_size);
  else stepSizeSlider->setValue(0.01);
  stepSizeSlider->getValueChangedCallbacks().add(this, &DrivenVanDerPolParameterDialog::sliderCallback);


  factory.createLabel("EvaluationLabel", "Evaluation Method");
  GLMotif::ToggleButton* exactEvalToggle=factory.createCheckBox("ExactEvalToggle", "Exact", true);
  GLMotif::ToggleButton* gridEvalToggle=factory.createCheckBox("GridEvalToggle", "Interpolated Grid");
  // assign line style toggle callbacks
  exactEvalToggle->getValueChangedCallbacks().add(this, &DrivenVanDerPolParameterDialog::evalTogglesCallback);
  gridEvalToggle->getValueChangedCallbacks().add(this, &DrivenVanDerPolParameterDialog::evalTogglesCallback);

  factory.createLabel("xSpacingLabel", "x-Grid Spacing");
  currentXValue=factory.createTextField("xTextField", 12);
  currentXValue->setString("1.0");
  currentXValue->setCharWidth(5);
  currentXValue->setPrecision(5);
  xSpacingSlider=factory.createSlider("XSpacingSlider", 15.0);
  xSpacingSlider->setValueRange(.001, 2.0, 0.001);
  xSpacingSlider->setValue(1.0);
  xSpacingSlider->getValueChangedCallbacks().add(this, &DrivenVanDerPolParameterDialog::sliderCallback);

  factory.createLabel("ySpacingLabel", "y-Grid Spacing");
  currentYValue=factory.createTextField("yTextField", 12);
  currentYValue->setString("1.0");
  currentYValue->setCharWidth(5);
  currentYValue->setPrecision(5);  ySpacingSlider=factory.createSlider("YSpacingSlider", 15.0);
  ySpacingSlider->setValueRange(.001, 2.0, 0.001);
  ySpacingSlider->setValue(1.0);
  ySpacingSlider->getValueChangedCallbacks().add(this, &DrivenVanDerPolParameterDialog::sliderCallback);

  factory.createLabel("zSpacingLabel", "z-Grid Spacing");
  currentZValue=factory.createTextField("zTextField", 12);
  currentZValue->setString("1.0");
  currentZValue->setCharWidth(5);
  currentZValue->setPrecision(5);
  zSpacingSlider=factory.createSlider("ZSpacingSlider", 15.0);
  zSpacingSlider->setValueRange(.001, 2.0, 0.001);
  zSpacingSlider->setValue(1.0);
  zSpacingSlider->getValueChangedCallbacks().add(this, &DrivenVanDerPolParameterDialog::sliderCallback);

  // add toggles to array for radio-button behavior
  evalToggles.push_back(exactEvalToggle);
  evalToggles.push_back(gridEvalToggle);

  parameterDialog->manageChild();
  return parameterDialogPopup;
}

void DrivenVanDerPolParameterDialog::sliderCallback(GLMotif::Slider::ValueChangedCallbackData* cbData)
{
  double value = cbData->value;

  char buff[10];
  snprintf(buff, sizeof(buff), "%3.2f", value);

  if (strcmp(cbData->slider->getName(), "BParameterSlider")==0)
    {
      currentBValue->setString(buff);
      model->setValue("b", value);
    }
  else if (strcmp(cbData->slider->getName(), "AParameterSlider")==0)
    {
      currentAValue->setString(buff);
      model->setValue("A", value);
    }
  else if (strcmp(cbData->slider->getName(), "WParameterSlider")==0)
    {
      currentWValue->setString(buff);
      model->setValue("w", value);
    }
  else if (strcmp(cbData->slider->getName(), "StepSizeSlider")==0)
  {
    snprintf(buff, sizeof(buff), "%6.4f", value);
    stepSizeValue->setString(buff);
    IntegrationStepSize::instance()->setValue(value);
    IntegrationStepSize::instance()->saveValue("Driven Van Der Pol", value);
  }

  else if (strcmp(cbData->slider->getName(), "XSpacingSlider")==0)
    {
      snprintf(buff, sizeof(buff), "%3.3f", value);
      currentXValue->setString(buff);
      model->setSpacing(0, value);
    }
  else if (strcmp(cbData->slider->getName(), "YSpacingSlider")==0)
    {
      snprintf(buff, sizeof(buff), "%3.3f", value);
      currentYValue->setString(buff);
      model->setSpacing(1, value);
    }
  else if (strcmp(cbData->slider->getName(), "ZSpacingSlider")==0)
    {
      snprintf(buff, sizeof(buff), "%3.3f", value);
      currentZValue->setString(buff);
      model->setSpacing(2, value);
    }
}

void DrivenVanDerPolParameterDialog::evalTogglesCallback(GLMotif::ToggleButton::ValueChangedCallbackData* cbData)
{
   std::string name=cbData->toggle->getName();

   if (name == "ExactEvalToggle")
   {
      model->setSimulate(false);
   }
   else if (name == "GridEvalToggle")
   {
      model->setSimulate(true);
   }

   // fake radio-button behavior
   for (ToggleArray::iterator button=evalToggles.begin(); button != evalToggles.end(); ++button)
      if (strcmp((*button)->getName(), name.c_str()) != 0 and (*button)->getToggle())
         (*button)->setToggle(false);
      else if (strcmp((*button)->getName(), name.c_str()) == 0)
         (*button)->setToggle(true);

}

