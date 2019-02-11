#include "Material.h"

Material::Material()
{
}

void Material::bind(ShaderProgram & sp)
{
	if (shiny != 0)
	{
		sp.uniform("u_material.shiny", shiny);
		glUniform3fv(sp.getUniformLocation("u_material.ka"), 1, &(ka[0]));
		glUniform3fv(sp.getUniformLocation("u_material.kd"), 1, &(kd[0]));
		glUniform3fv(sp.getUniformLocation("u_material.ks"), 1, &(ks[0]));
		

	} //sets some material data

}

