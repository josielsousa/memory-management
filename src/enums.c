#include "enums.h"

char *http_to_str(http_status_t status) {
  switch (status) {
  case STATUS_OK:
    return "200 OK";
  case STATUS_BAD_REQUEST:
    return "400 Bad Request";
  case STATUS_FORBIDDEN:
    return "403 Forbidden";
  case STATUS_NOT_FOUND:
    return "404 Not Found";
  case STATUS_INTERNAL_SERVER_ERROR:
    return "500 Internal Server Error";
  default:
    return "Unknown";
  }
}
