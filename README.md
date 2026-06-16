# logos-forum-app

The business logic layer for a decentralised forum built on the [Logos](https://logos.co) stack. This `core` module sits between the QML UI backend and `forum_comms`, coordinating post publishing, topic subscriptions, and identity management.

## What this is

`forum_app` is the middle layer of the forum stack:

- Receives calls from the forum UI backend over IPC
- Fetches the local identity from `forum_comms` and attaches it to outgoing posts
- Forwards publish/subscribe calls to `forum_comms`
- Re-emits `postReceived` events upward so the UI can update its post list

## Architecture

```
logos-forum  (QML UI module)
    ↓ QtRemoteObjects IPC
logos-forum-app  (forum_app — this repo)
    ↓ Logos IPC
logos-forum-comms  (forum_comms — delivery layer)
    ↓ logos-delivery SDK
logos-delivery  (ships in Basecamp)
    ↓ Network
```

## IPC interface

```cpp
// Called from UI backend
void publishPost(topic, content)
void subscribeTopic(topic)
void unsubscribeTopic(topic)
std::string getStatus()

// Events (forwarded up from forum_comms)
logos_events:
    void postReceived(topic, content, sender_id)
    void statusChanged(status)
```

## Inter-module calls

`forum_app` uses `modules().forum_comms` to reach the delivery layer:

```cpp
// In forum_app_impl.cpp
const std::string identity = modules().forum_comms.getIdentity();
modules().forum_comms.publishPost(topic, content, identity);
```

## Building

Requires [logos-module-builder](https://github.com/logos-co/logos-module-builder), [logos-forum-comms](https://github.com/lobsterscollide/logos-forum-comms), and Nix with flakes enabled.

```bash
nix build
```

## Structure

```
logos-forum-app/
├── flake.nix
├── metadata.json
├── CMakeLists.txt
└── src/
    ├── forum_app_impl.h
    └── forum_app_impl.cpp
```

## References

- [logos-module-builder](https://github.com/logos-co/logos-module-builder)
- [logos-forum-comms](https://github.com/lobsterscollide/logos-forum-comms) — delivery layer dependency
- [logos-forum](https://github.com/lobsterscollide/logos-forum) — QML UI module
- [forum-sample-app](https://github.com/logos-co/forum-sample-app) — Logos reference architecture
