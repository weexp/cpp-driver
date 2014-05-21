#include "session_future.hpp"

#include "session.hpp"

namespace cass {

Future::ResultOrError* ShutdownSessionFuture::get() {
  Future::ResultOrError* result_or_error = Future::get();
  session->join();
  return result_or_error;
}

void ShutdownSessionFuture::wait() {
  Future::wait();
  session->join();
}

bool ShutdownSessionFuture::wait_for(size_t timeout) {
  if(Future::wait_for(timeout)) {
    // TODO(mpenick): Not ideal because this could take longer than timeout
    session->join();
    return true;
  }
  return false;
}

} // namespace cass
