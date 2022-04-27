#ifndef __STRING_VIEW_H__
#define __STRING_VIEW_H__

#include <stdbool.h>
#include <string.h>
#include <assert.h>

#ifndef SV_MAX_BUFFER_SIZE
#define SV_MAX_BUFFER_SIZE 1024
#endif // SV_MAX_BUFFER_SIZE

typedef struct {
  size_t size;
  const char *data;
} StringView;

// This was stolen from Tsoding: https://github.com/tsoding/sv/blob/master/sv.h
// printf macros for String_View
#define SV_FMT "%.*s"
#define SV_ARG(sv) (int) (sv).size, (sv).data
// USAGE:
//   StringView name = ...;
//   printf("Name: "SV_FMT"\n", SV_ARG(name));

#define SV(string) sv_from_cstr(string)

StringView sv_from_portion(const char *cstr, size_t size);
StringView sv_from_cstr(const char *cstr);

void sv_split(StringView sv, const char delim, StringView *output);
StringView sv_split_first(StringView sv, const char delim, StringView *remain);

StringView sv_trim(StringView sv);
StringView sv_ltrim(StringView sv);
StringView sv_rtrim(StringView sv);

StringView sv_join(StringView sv1, StringView sv2);

StringView sv_replace_first(StringView sv, StringView delim);
StringView sv_replace_all(StringView sv, StringView delim);

StringView sv_to_upper(StringView sv);
StringView sv_to_lower(StringView sv);
StringView sv_captialize(StringView sv);

bool sv_starts_with(StringView sv, StringView prefix);
bool sv_ends_with(StringView sv, StringView suffix);

bool sv_equals(StringView sv1, StringView sv2);
bool sv_equals_ignore_cases(StringView sv1, StringView sv2);

bool sv_is_alpha(StringView sv);
bool sv_is_numeric(StringView sv);
bool sv_is_alnum(StringView sv);

#ifdef STRING_VIEW_IMPLEMENTATION

bool sv_util_is_alpha(const char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool sv_util_is_number(const char n) {
  return (n >= '0' && n <= '9');
}

StringView sv_from_portion(const char *cstr, size_t size) {
  StringView sv;
  sv.size = size;
  sv.data = cstr;
  return sv;
}

StringView sv_from_cstr(const char *cstr) {
  return sv_from_portion(cstr, strlen(cstr));
}

// TODO: Give the user the error
// if the length of the `output` array
// provided has been exceed
void sv_split(StringView sv, const char delim, StringView *output) {
  StringView remain;
  StringView first;
  size_t index = 0;

  sv = sv_trim(sv);
  while(true) {
    first = sv_split_first(sv, delim, &remain);
    if (first.size == 0) break;
    output[index++] = first;
    sv = remain;
  }
  output[index++] = remain;
}

StringView sv_split_first(StringView sv, const char delim, StringView *remain) {
  if (sv.data == NULL) return sv_from_portion(NULL, 0);

  size_t index = 0;
  for (size_t i = 0; i < sv.size; ++i) {
    if (sv.data[i] != delim) index++;
    else break;
  }
  if (index == sv.size) {
    return sv_from_portion(NULL, 0);
  } else {
    *remain = sv_from_portion(sv.data + index + 1, sv.size - index - 1);
    return sv_from_portion(sv.data, index);
  }
}

StringView sv_trim(StringView sv) {
  sv = sv_ltrim(sv);
  sv = sv_rtrim(sv);
  return sv;
}

StringView sv_ltrim(StringView sv) {
  int index = 0;
  for(size_t i = 0; i < sv.size; ++i) {
    if (sv.data[i] == ' ' || sv.data[i] == '\t' || sv.data[i] == '\n') index++;
    else break;
  }

  return sv_from_portion(sv.data + index, sv.size - index);
}

StringView sv_rtrim(StringView sv) {
  int index = 0;
  for(size_t i = sv.size - 1; i > 0; --i) {
    if (sv.data[i] == ' ' || sv.data[i] == '\t' || sv.data[i] == '\n') index++;
    else break;
  }

  return sv_from_portion(sv.data, sv.size - index);
}

StringView sv_join(StringView sv1, StringView sv2) {
  StringView res;
  (void) sv1;
  (void) sv2;
  assert(0 && "`sv_join` is not implemented yet\n");
  return res;
}

StringView sv_replace_first(StringView sv, StringView delim) {
  StringView res;
  (void) sv;
  (void) delim;
  assert(0 && "`sv_replace_first` is not implemented yet\n");
  return res;
}

StringView sv_replace_all(StringView sv, StringView delim) {
  StringView res;
  (void) sv;
  (void) delim;
  assert(0 && "`sv_replace_all` is not implemented yet\n");
  return res;
}

StringView sv_to_upper(StringView sv) {
  StringView res;
  (void) sv;
  assert(0 && "`sv_to_upper` is not implemented yet\n");
  return res;
}

StringView sv_to_lower(StringView sv) {
  StringView res;
  (void) sv;
  assert(0 && "`sv_to_lower` is not implemented yet\n");
  return res;
}

StringView sv_captialize(StringView sv) {
  StringView res;
  (void) sv;
  assert(0 && "`sv_captialize` is not implemented yet\n");
  return res;
}

bool sv_starts_with(StringView sv, StringView prefix) {
  if (prefix.size > sv.size) return false;
  sv = sv_from_portion(sv.data, prefix.size);
  return sv_equals(sv, prefix);
}

bool sv_ends_with(StringView sv, StringView suffix) {
  if (suffix.size > sv.size) return false;
  sv = sv_from_portion(sv.data + (sv.size - suffix.size), suffix.size);
  return sv_equals(sv, suffix);
}

bool sv_equals(StringView sv1, StringView sv2) {
  if (sv1.size != sv2.size) return false;
  
  for (size_t i = 0; i < sv1.size; ++i) {
    if (sv1.data[i] != sv2.data[i]) return false;
  }

  return true;
}

bool sv_equals_ignore_cases(StringView sv1, StringView sv2) {
  if (sv1.size != sv2.size) return false;
  sv1 = sv_to_lower(sv1);
  sv2 = sv_to_lower(sv2);

  for (size_t i = 0; i < sv1.size; ++i) {
    if (sv1.data[i] != sv2.data[i]) return false;
  }

  return true;
}

bool sv_is_alpha(StringView sv) {
  for (size_t i = 0; i < sv.size; ++i) {
    if (!sv_util_is_alpha(sv.data[i])) return false;
  }
  return true;
}

bool sv_is_numeric(StringView sv) {
  for (size_t i = 0; i < sv.size; ++i) {
    if (!sv_util_is_number(sv.data[i])) return false;
  }

  return true;
}

bool sv_is_alnum(StringView sv) {
  for (size_t i = 0; i < sv.size; ++i) {
    if (!sv_util_is_number(sv.data[i]) && !sv_util_is_alpha(sv.data[i])) return false;
  }

  return true;
}

#endif // STRING_VIEW_IMPLEMENTATION
#endif // __STRING_VIEW_H__
