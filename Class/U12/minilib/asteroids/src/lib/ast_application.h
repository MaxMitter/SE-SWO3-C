#pragma once

#include <ml5/ml5.h>
#include "ast_window.h"

class ast_application : public ml5::application, MI5_DERIVE(ast_application, ml5::application) {
	MI5_INJECT(ast_application)

	std::unique_ptr <ml5::window> make_window() const override {
		return std::make_unique<ast_window>();
	}
};