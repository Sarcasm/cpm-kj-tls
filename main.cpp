#include <kj/async-io.h>
#include <kj/compat/tls.h>

int main() {
  auto io = kj::setupAsyncIo();
  kj::TlsContext::Options options;
  options.useSystemTrustStore = false;
  kj::TlsContext tls(options);

  auto& network = io.provider->getNetwork();
  auto addr = network.parseAddress("*", 80).wait(io.waitScope);
  auto listener = tls.wrapPort(addr->listen());
  auto connection = listener->accept().wait(io.waitScope);
  connection->write("HTTP/1.1 404 Not Found\r\n\r\n", 26).wait(io.waitScope);

  return 0;
}
