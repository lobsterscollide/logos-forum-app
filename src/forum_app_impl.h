#pragma once

#include <string>
#include <logos_module_context.h>

// Forum App — business logic layer between the UI module and forum_comms.
//
// Receives calls from the UI backend over IPC, enriches them (e.g. attaches
// the local identity), and forwards to forum_comms. Re-emits incoming posts
// upward so the UI backend can update its post list.
class ForumAppImpl : public LogosModuleContext {
public:
    ForumAppImpl() = default;
    ~ForumAppImpl() = default;

    // Publish a post — fetches local identity from forum_comms, then
    // forwards the full message to forum_comms.publishPost.
    void publishPost(const std::string &topic, const std::string &content);

    void subscribeTopic(const std::string &topic);
    void unsubscribeTopic(const std::string &topic);

    // Returns current status string for diagnostics.
    std::string getStatus();

// clang-format off
logos_events:
    // Re-emitted from forum_comms.postReceived — UI backend subscribes here.
    void postReceived(const std::string &topic,
                      const std::string &content,
                      const std::string &sender_id);

    void statusChanged(const std::string &status);
// clang-format on

private:
    std::string status_{"initialising"};

    void setStatus(const std::string &s);
};
