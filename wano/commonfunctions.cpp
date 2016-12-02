#include "commonfunctions.h"
#include "services.h"
#include "nameddocument.h"

using namespace std;

namespace wano {
	namespace functions {
		void saveCurrentDocument() {
			auto& ndoc = services::currentNamedDocument::get();
			if (!ndoc.hasFile())
				return;
			ndoc.toFile();
		}
	}
}