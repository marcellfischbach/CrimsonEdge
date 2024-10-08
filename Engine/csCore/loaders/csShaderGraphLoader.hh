//
// Created by Marcell on 07.07.2024.
//

#pragma once

#include <csCore/csCoreExport.hh>
#include <csCore/resource/csBaseCSFAssetLoader.hh>

namespace cryo
{

class csSGNode;
class csSGResourceNode;
class csShaderGraph;

CS_CLASS()
class CS_CORE_API csShaderGraphLoader : public CS_SUPER(csBaseCSFAssetLoader)
{
CS_CLASS_GEN_OBJECT;
public:
  csShaderGraphLoader();
  ~csShaderGraphLoader() override = default;

  iObject *Load(const csCryoFile *file, const csClass *cls, const csResourceLocator &locator) const override;

private:
  void LoadQueue(const csCryoFileElement *shaderGraphElement, csShaderGraph *sg) const;
  void LoadLightingMode(const csCryoFileElement *shaderGraphElement, csShaderGraph *sg) const;
  void LoadBlendingMode(const csCryoFileElement *shaderGraphElement, csShaderGraph *sg) const;

  csSGNode *CreateNode(const csCryoFileElement *nodeElement, csShaderGraph *sg) const;
  csSGResourceNode *CreateResourceNode(const csCryoFileElement *nodeElement, csShaderGraph *sg) const;
  bool LoadNodeBindingsAndValues(const csCryoFileElement *nodeElement, csSGNode *node, csShaderGraph *sg) const;
  bool LoadValue(const csCryoFileElement *valueElement, csSGNode *node, csShaderGraph *sg) const;
  bool LoadBinding(const csCryoFileElement *valueElement, csSGNode *node, csShaderGraph *sg) const;

  void LoadAttributes(const csCryoFileElement *attributesElement, csShaderGraph *sg, const csResourceLocator &locator) const;
  void LoadAttribute(const csCryoFileElement *attributeElement, csShaderGraph *sg, const csResourceLocator &locator) const;


};

} // ce
