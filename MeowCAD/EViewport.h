#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <cstdint>

class EViewport{
	//uint32_t height, width;
	GLuint FramebufferName; 
	GLint origFB;

	bool is_viewport_window_active{true};
	bool dirty{};
	glm::ivec2 resolution{ 0,0 };
	GLuint renderedTexture;

public:
	GLuint texID() {
		return renderedTexture;
	}
	bool is_active() {
		return is_viewport_window_active;
	}
	bool& get_active() {
		return is_viewport_window_active;
	}
	void set_active(bool value) {
		is_viewport_window_active = value;
	}
	bool is_dirty() {
		return dirty;
	}
	void set_dirty(bool value) {
		dirty = value;
	}
	glm::ivec2 get_resolution(){
		return resolution;
	}
	void set_resolution(glm::ivec2 resolution) {
		this->resolution = resolution;
	}
	void set(uint32_t texture_width, uint32_t texture_height) {
		resolution.x = texture_width;
		resolution.y = texture_height;

		// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
		FramebufferName = 0;
		glGenFramebuffers(1, &FramebufferName);
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	
		// The texture we're going to render to
		renderedTexture;
		glGenTextures(1, &renderedTexture);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, renderedTexture);

		// Give an empty image to OpenGL ( the last "0" )
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resolution.x, resolution.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

		// Poor filtering. Needed !
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



		// The depth buffer
		GLuint depthrenderbuffer;
		glGenRenderbuffers(1, &depthrenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, resolution.x, resolution.y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

		// Set "renderedTexture" as our colour attachement #0
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

		// Set the list of draw buffers.
		GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

		// Always check that our framebuffer is ok
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			static_assert("EViewport Framebuffer creation failed.\n");

	}

	void rescale_frame_buffer(glm::ivec2 texture_resolution) // what will happen to old buffer? 
	{
		resolution = texture_resolution;

		//glDeleteTextures(1, &renderedTexture);
		glBindTexture(GL_TEXTURE_2D, renderedTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resolution.x, resolution.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, FramebufferName);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, resolution.x, resolution.y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, FramebufferName);
	}


	void bind() {
		glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &origFB);

		// Render to our framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
		glViewport(0, 0, resolution.x, resolution.y); // Render on the whole framebuffer, complete from the lower left corner to the upper right
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}

	void unbind(uint32_t scr_width, uint32_t scr_height) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, scr_width, scr_height);
	}
};
