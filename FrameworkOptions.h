#pragma once

struct FrameworkOptions {

	unsigned int gl_version_major_;
	unsigned int gl_version_minor_;

	unsigned int window_width_;
	unsigned int window_height_;

	unsigned int render_width_;
	unsigned int render_height_;

	float fov_;

	float near_plane_;
	float far_plane_;

	FrameworkOptions() {
		gl_version_major_ = 3;
		gl_version_minor_ = 3;

		window_width_ = 1280;
		window_height_ = 720;

		render_width_ = 1280;
		render_height_ = 720;

		fov_ = 80.f;

		near_plane_ = 0.1f;
		far_plane_ = 100.f;
	}

};