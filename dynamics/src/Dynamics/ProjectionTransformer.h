#ifndef DTS_PROJECTION_TRANSFORMER
#define DTS_PROJECTION_TRANSFORMER

#include "Parameter.h"
#include "Transformer.h"

template <typename ScalarParam>
class ProjectionTransformer : public Transformer<ScalarParam>
{

public:

    ProjectionTransformer(DynamicalModel<ScalarParam> const& model);
    virtual ~ProjectionTransformer();

    virtual void transform(typename DynamicalModel<ScalarParam>::Vector const& v, 
                           typename DynamicalModel<ScalarParam>::Vector & out);
};


//
// Implementation
//

template <typename ScalarParam>
ProjectionTransformer<ScalarParam>::ProjectionTransformer(DynamicalModel<ScalarParam> const& model)
: Transformer<ScalarParam>(model)
{
    this->setName("projection");
    
    // Determine appropriate defaults
    int d = model.getDimension();
    int x = 0;
    int y = (d > 1 ? 1 : -1);
    int z = (d > 2 ? 2 : -1);

    typedef typename ParameterClass<ScalarParam>::IntParameter IntParameter;

    addIntParameter( IntParameter("xCoordinate", x, -1, d-1, x, 1) );
    addIntParameter( IntParameter("yCoordinate", y, -1, d-1, y, 1) );
    addIntParameter( IntParameter("zCoordinate", z, -1, d-1, z, 1) );        
}

template <typename ScalarParam>
ProjectionTransformer<ScalarParam>::~ProjectionTransformer()
{
}


template <typename ScalarParam>
inline
void ProjectionTransformer<ScalarParam>::transform(typename DynamicalModel<ScalarParam>::Vector const& v, 
                                                   typename DynamicalModel<ScalarParam>::Vector & out)
{
    // A value of -1 means it will be mapped to the value 0.
    int const& xIndex = this->intParamValues[0];
    int const& yIndex = this->intParamValues[1];
    int const& zIndex = this->intParamValues[2];    
    
    out[0] = ( xIndex == -1 ? 0 : v[ xIndex ] );
    out[1] = ( yIndex == -1 ? 0 : v[ yIndex ] );
    out[2] = ( zIndex == -1 ? 0 : v[ zIndex ] );
}


#endif