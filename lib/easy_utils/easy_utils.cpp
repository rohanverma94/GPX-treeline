//
// Created by rohandev on 7/23/23.
//

#include "easy_utils.h"

#include <cstring>
#include <cstdlib>
/*
 * Look at https://cwe.mitre.org/data/definitions/467.html
 * sizeof() on a pointer can produce side effect on malloc()!
 * sizeof(...)` on the pointer type can result in a dynamic allocation being dumped into the pointer.
 * This could not be caught because C's malloc() yields void*.
 * If malloc() had a typed returned, this would have been caught by the type system.
 */
#define safe_alloc(...) \
     (__VA_ARGS__*)malloc(sizeof(__VA_ARGS__))


/*
 * Small String optimization, inspired from Andrei Alexanderescu's Loki library
*/
class stringsso {
public:
	stringsso() = default;

	explicit stringsso(const char *s) :
			s_((strlen(s) + 1 < sizeof(buf_)) ? strcpy(buf_, s)
											  : strdup(s)) {}

	stringsso(const stringsso &s) :
			s_((s.s_ == s.buf_) ? strcpy(buf_, s.buf_)
								: strdup(s.s_)) {}

	stringsso &operator=(const char *s) {
		if (s_ != buf_) free(s_);
		s_ = (strlen(s) + 1 < sizeof(buf_)) ? strcpy(buf_, s)
											: strdup(s);
		return *this;
	}

	stringsso &operator=(const stringsso &s) {
		if (this == &s) return *this;
		if (s_ != buf_) free(s_);
		s_ = (s.s_ == s.buf_) ? strcpy(buf_, s.buf_)
							  : strdup(s.s_);
		return *this;
	}

	bool operator==(const stringsso &rhs) const {
		return strcmp(s_, rhs.s_) == 0;
	}

	~stringsso() {
		if (s_ != buf_) free(s_);
	}

private:
	char *s_ = nullptr;
	char buf_[16];
};
