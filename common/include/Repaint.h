// Repaint common header

class Repaint
{
private:

	enum Programs
	{
		PROGRAM_FRAME,
		PROGRAM_REPAINT,
		PROGRAM_COLORING,
		NUMBER_OF_PROGRAMS
	};
	GLuint m_auProgramIds[NUMBER_OF_PROGRAMS];


	enum FrameAttributes
	{
		ATTRIBUTE_FRAME_...,
		NUMBER_OF_FRAME_ATTRIBUTES
	};
	GLuint m_auFrameAttributeIds[NUMBER_OF_FRAME_ATTRIBUTES];

	enum FrameUniforms
	{
		UNIFORM_FRAME_...,
		NUMBER_OF_FRAME_UNIFORMS
	};
	GLuint m_auFrameUniformIds[NUMBER_OF_FRAME_UNIFORMS];


	enum RepaintAttributes
	{
		ATTRIBUTE_REPAINT_...,
		NUMBER_OF_REPAINT_ATTRIBUTES
	};
	GLuint m_auRepaintAttributeIds[NUMBER_OF_REPAINT_ATTRIBUTES];

	enum RepaintUniforms
	{
		UNIFORM_REPAINT_...,
		NUMBER_OF_REPAINT_UNIFORMS
	};
	GLuint m_auRepaintUniformIds[NUMBER_OF_REPAINT_UNIFORMS];


	enum ColoringAttributes
	{
		ATTRIBUTE_COLORING_...,
		NUMBER_OF_COLORING_ATTRIBUTES
	};
	GLuint m_auColoringAttributeIds[NUMBER_OF_COLORING_ATTRIBUTES];

	enum ColoringUniforms
	{
		UNIFORM_COLORING_...,
		NUMBER_OF_COLORING_UNIFORMS
	};
	GLuint m_auColoringUniformIds[NUMBER_OF_COLORING_UNIFORMS];


	enum TextureIds
	{
		TEXTURE_LUMINANCE,
		TEXTURE_CHROMINANCE,
		TEXTURE_REPAINT,
		TEXTURE_ARROW,
		NUMBER_OF_TEXTURES
	};
	GLuint m_auTextureIds[NUMBER_OF_TEXTURES];


	enum VertexBufferObjects
	{
		BUFFER_FRAME,
		BUFFER_REPAINT,
		BUFFER_ARROW_LEFT,
		BUFFER_ARROW_RIGHT,
		NUMBER_OF_BUFFERS
	};
	GLuint m_auBufferIds[NUMBER_OF_BUFFERS];


	enum VertexArrayObjects
	{
		ARRAY_FRAME,
		ARRAY_REPAINT,
		ARRAY_ARROW_LEFT,
		ARRAY_ARROW_RIGHT,
		NUMBER_OF_ARRAYS
	};
	GLuint m_auArrayIds[NUMBER_OF_ARRAYS];


	enum FramebufferObjects
	{
		FRAMEBUFFER_ONSCREEN,
		FRAMEBUFFER_OFFSCREEN,
		NUMBER_OF_FRAMEBUFFERS
	};
	GLuint m_auFramebufferIds[NUMBER_OF_FRAMEBUFFERS];

};
