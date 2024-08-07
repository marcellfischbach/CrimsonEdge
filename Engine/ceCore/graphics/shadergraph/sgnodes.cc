
#include <ceCore/graphics/shadergraph/sgnodes.hh>

namespace ce
{


/* *********************************************************/
/*     Const Float                                         */
/* *********************************************************/

const std::string SGConstFloat::OUT_V = "V";
SGConstFloat::SGConstFloat()
    : SGNode("Const Float")
{
  DefineInput("X", eSGValueType::Invalid);
  DefineOutput(OUT_V, eSGValueType::Float);
}

void SGConstFloat::SetValue(float x)
{
  GetInput(0)->SetScalar(x);
}

void SGConstFloat::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Float);
}



/* *********************************************************/
/*     Const Vector 2                                      */
/* *********************************************************/

const std::string SGConstVec2::OUT_V = "V";


SGConstVec2::SGConstVec2()
    : SGNode("Const Vec2")
{
  DefineInput("X", eSGValueType::Invalid);
  DefineInput("Y", eSGValueType::Invalid);
  DefineOutput(OUT_V, eSGValueType::Vector2);
}

void SGConstVec2::SetValue(float x, float y)
{
  GetInput(0)->SetScalar(x);
  GetInput(1)->SetScalar(y);
}


void SGConstVec2::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Vector2);
}


/* *********************************************************/
/*     Const Vector 3                                      */
/* *********************************************************/


const std::string SGConstVec3::OUT_V = "V";
SGConstVec3::SGConstVec3()
    : SGNode("Const Vec3")
{
  DefineInput("X", eSGValueType::Invalid);
  DefineInput("Y", eSGValueType::Invalid);
  DefineInput("Z", eSGValueType::Invalid);
  DefineOutput(OUT_V, eSGValueType::Vector3);
}

void SGConstVec3::SetValue(float x, float y, float z)
{
  GetInput(0)->SetScalar(x);
  GetInput(1)->SetScalar(y);
  GetInput(2)->SetScalar(z);
}

void SGConstVec3::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Vector3);

}

/* *********************************************************/
/*     Const Vector 4                                      */
/* *********************************************************/
const std::string SGConstVec4::OUT_V = "V";

SGConstVec4::SGConstVec4()
    : SGNode("Const Vec4")
{
  DefineInput("X", eSGValueType::Invalid);
  DefineInput("Y", eSGValueType::Invalid);
  DefineInput("Z", eSGValueType::Invalid);
  DefineInput("W", eSGValueType::Invalid);
  DefineOutput(OUT_V, eSGValueType::Vector4);
}


void SGConstVec4::SetValue(float x, float y, float z, float w)
{
  GetInput(0)->SetScalar(x);
  GetInput(1)->SetScalar(y);
  GetInput(2)->SetScalar(z);
  GetInput(3)->SetScalar(w);
}

void SGConstVec4::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Vector4);
}




/* *********************************************************/
/*     Const Color 3                                       */
/* *********************************************************/

const std::string SGConstColor3::OUT_V = "V";

SGConstColor3::SGConstColor3()
    : SGNode("Const Color3")
{
  DefineInput("R", eSGValueType::Invalid);
  DefineInput("G", eSGValueType::Invalid);
  DefineInput("B", eSGValueType::Invalid);
  DefineOutput(OUT_V, eSGValueType::Vector3);
}

void SGConstColor3::SetValue(float r, float g, float b)
{
  GetInput(0)->SetScalar(r);
  GetInput(1)->SetScalar(g);
  GetInput(2)->SetScalar(b);
}

void SGConstColor3::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Vector3);
}



/* *********************************************************/
/*     Const Color 4                                       */
/* *********************************************************/

const std::string SGConstColor4::OUT_V = "V";

SGConstColor4::SGConstColor4()
    : SGNode("Const Color4")
{
  DefineInput("R", eSGValueType::Invalid);
  DefineInput("G", eSGValueType::Invalid);
  DefineInput("B", eSGValueType::Invalid);
  DefineInput("A", eSGValueType::Invalid);
  DefineOutput(OUT_V, eSGValueType::Vector3);
}

void SGConstColor4::SetValue(float r, float g, float b, float a)
{
  GetInput(0)->SetScalar(r);
  GetInput(1)->SetScalar(g);
  GetInput(2)->SetScalar(b);
  GetInput(3)->SetScalar(a);
}

void SGConstColor4::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Vector4);
}


/* *********************************************************/
/*     Vec 2                                               */
/* *********************************************************/

const std::string SGVec2::IN_X  = "X";
const std::string SGVec2::IN_Y  = "Y";
const std::string SGVec2::OUT_V = "V";

SGVec2::SGVec2()
    : SGNode("Vec2")
{
  DefineInput(IN_X, eSGValueType::Float);
  DefineInput(IN_Y, eSGValueType::Float);
  DefineOutput(OUT_V, eSGValueType::Vector2);
}

void SGVec2::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Vector2);
}




/* *********************************************************/
/*     Vec 3                                               */
/* *********************************************************/

const std::string SGVec3::IN_X  = "X";
const std::string SGVec3::IN_Y  = "Y";
const std::string SGVec3::IN_Z  = "Z";
const std::string SGVec3::OUT_V = "V";

SGVec3::SGVec3()
    : SGNode("Vec3")
{
  DefineInput(IN_X, eSGValueType::Float);
  DefineInput(IN_Y, eSGValueType::Float);
  DefineInput(IN_Z, eSGValueType::Float);
  DefineOutput(OUT_V, eSGValueType::Vector3);
}

void SGVec3::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Vector3);
}




/* *********************************************************/
/*     Vec 4                                               */
/* *********************************************************/

const std::string SGVec4::IN_X  = "X";
const std::string SGVec4::IN_Y  = "Y";
const std::string SGVec4::IN_Z  = "Z";
const std::string SGVec4::IN_W  = "W";
const std::string SGVec4::OUT_V = "V";

SGVec4::SGVec4()
    : SGNode("Vec4")
{
  DefineInput(IN_X, eSGValueType::Float);
  DefineInput(IN_Y, eSGValueType::Float);
  DefineInput(IN_Z, eSGValueType::Float);
  DefineInput(IN_W, eSGValueType::Float);
  DefineOutput(OUT_V, eSGValueType::Vector4);
}

void SGVec4::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Vector3);
}

/* *********************************************************/
/*     Decompose Vec 2                                     */
/* *********************************************************/

const std::string SGDecomposeVec2::IN_V  = "V";
const std::string SGDecomposeVec2::OUT_X = "X";
const std::string SGDecomposeVec2::OUT_Y = "Y";

SGDecomposeVec2::SGDecomposeVec2()
    : SGNode("Decompose Vec2")
{
  DefineInput(IN_V, eSGValueType::Vector2);
  DefineOutput(OUT_X, eSGValueType::Float);
  DefineOutput(OUT_Y, eSGValueType::Float);
}

void SGDecomposeVec2::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Float);
  GetOutput(1)->SetValueType(eSGValueType::Float);
}


/* *********************************************************/
/*     Decompose Vec 3                                     */
/* *********************************************************/

const std::string SGDecomposeVec3::IN_V  = "V";
const std::string SGDecomposeVec3::OUT_X = "X";
const std::string SGDecomposeVec3::OUT_Y = "Y";
const std::string SGDecomposeVec3::OUT_Z = "Z";

SGDecomposeVec3::SGDecomposeVec3()
    : SGNode("Decompose Vec3")
{
  DefineInput(IN_V, eSGValueType::Vector3);
  DefineOutput(OUT_X, eSGValueType::Float);
  DefineOutput(OUT_Y, eSGValueType::Float);
  DefineOutput(OUT_Z, eSGValueType::Float);
}

void SGDecomposeVec3::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Float);
  GetOutput(1)->SetValueType(eSGValueType::Float);
  GetOutput(2)->SetValueType(eSGValueType::Float);
}


/* *********************************************************/
/*     Decompose Vec 4                                     */
/* *********************************************************/

const std::string SGDecomposeVec4::IN_V  = "V";
const std::string SGDecomposeVec4::OUT_X = "X";
const std::string SGDecomposeVec4::OUT_Y = "Y";
const std::string SGDecomposeVec4::OUT_Z = "Z";
const std::string SGDecomposeVec4::OUT_W = "W";

SGDecomposeVec4::SGDecomposeVec4()
    : SGNode("Decompose Vec4")
{
  DefineInput(IN_V, eSGValueType::Vector4);
  DefineOutput(OUT_X, eSGValueType::Float);
  DefineOutput(OUT_Y, eSGValueType::Float);
  DefineOutput(OUT_Z, eSGValueType::Float);
  DefineOutput(OUT_W, eSGValueType::Float);
}

void SGDecomposeVec4::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Float);
  GetOutput(1)->SetValueType(eSGValueType::Float);
  GetOutput(2)->SetValueType(eSGValueType::Float);
  GetOutput(3)->SetValueType(eSGValueType::Float);
}




/* *********************************************************/
/*     Binary operator                                     */
/* *********************************************************/

const std::string SGBinaryOperator::OUT_V = "V";

SGBinaryOperator::SGBinaryOperator(const std::string &name, eOperator op)
    : SGNode(name)
    , m_op(op)
{
  DefineInput("A", eSGValueType::All);
  DefineInput("B", eSGValueType::All);
  DefineOutput(OUT_V, eSGValueType::All);
}


SGBinaryOperator::eOperator SGBinaryOperator::GetOperator() const
{
  return m_op;
}

void SGBinaryOperator::CalcIOTypes()
{
  auto s0  = GetInput(0)->GetInputValueType();
  auto s1  = GetInput(1)->GetInputValueType();
  auto out = GetOutput(0);

  out->SetValueType(EvalValueType(s0, s1));
}

SGAdd::SGAdd() : SGBinaryOperator("Add", eOperator::Add)
{
}

SGSub::SGSub() : SGBinaryOperator("Sub", eOperator::Sub)
{
}

SGMul::SGMul() : SGBinaryOperator("Mul", eOperator::Mul)
{
}

SGDiv::SGDiv() : SGBinaryOperator("Div", eOperator::Div)
{
}

SGMod::SGMod() : SGBinaryOperator("Mod", eOperator::Mod)
{
}





/* *********************************************************/
/*     Streaming input                                     */
/* *********************************************************/


SGStreamNode::SGStreamNode(const std::string &name, eVertexStream stream, eSGValueType type)
    : SGNode(name)
    , m_stream(stream)
    , m_type(type)
{
  DefineOutput("V", type);
}

void SGStreamNode::CalcIOTypes()
{
  GetOutput(0)->SetValueType(m_type);
}

eVertexStream SGStreamNode::GetStream() const
{
  return m_stream;
}


SGTexCoord::SGTexCoord()
    : SGStreamNode("TexCoord", eVS_UV, eSGValueType::Vector2)
{

}


SGResourceNode::SGResourceNode(const std::string &name, eMaterialAttributeType matType)
    : SGNode(name)
    , m_matType(matType)
{

}


void SGResourceNode::SetResourceName(const std::string &name)
{
  m_resourceName = name;
}

const std::string &SGResourceNode::GetResourceName() const
{
  return m_resourceName;
}

eMaterialAttributeType SGResourceNode::GetMatType() const
{
  return m_matType;
}


SGResourceFloat::SGResourceFloat()
: SGResourceNode("Resource Float", eMAT_Float)
{
  DefineOutput("V", eSGValueType::Float);
}

void SGResourceFloat::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Float);
}


SGResourceColor3::SGResourceColor3()
    : SGResourceNode("Resource Color3", eMAT_Vec3)
{
  DefineOutput("V", eSGValueType::Vector3);
}

void SGResourceColor3::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Vector3);
}


SGTexture1D::SGTexture1D()
    : SGResourceNode("Texture1D", eMAT_Texture)
{
  DefineInput("UV", eSGValueType::Float);
  DefineOutput("Color", eSGValueType::Vector4);
}


void SGTexture1D::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Vector4);
}

SGTexture2D::SGTexture2D()
    : SGResourceNode("Texture2D", eMAT_Texture)
{
  DefineInput("UV", eSGValueType::Vector2);
  DefineOutput("Color", eSGValueType::Vector4);
}


void SGTexture2D::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Vector4);
}

SGTexture3D::SGTexture3D()
    : SGResourceNode("Texture3D", eMAT_Texture)
{
  DefineInput("UV", eSGValueType::Vector3);
  DefineOutput("Color", eSGValueType::Vector4);
}


void SGTexture3D::CalcIOTypes()
{
  GetOutput(0)->SetValueType(eSGValueType::Vector4);
}


} // ce