#pragma once

#include <string>
#include <logos_module_context.h>

// Forum App — business logic layer between the UI module and forum_comms.
//
// Receives calls from the UI backend over IPC, enriches them (e.g. attaches
// the local identity), and forwards to forum_comms. Re-emits incoming posts
// upward so the UI backend can update its post list.
//
// V1: one default forum ("Logos Forum"). The module auto-subscribes on init.
// V2: subscribeToForum/unsubscribeFromForum enable multiple forums.
class ForumAppImpl : public LogosModuleContext {
public:
    ForumAppImpl();
    ~ForumAppImpl() = default;

    // Publish a post to a specific forum topic. Attaches the local identity
    // (author's public key) from forum_comms before forwarding.
    void publishPost(const std::string &forum,
                     const std::string &topic,
                     const std::string &content);

    void subscribeToForum(const std::string &forum);
    void unsubscribeFromForum(const std::string &forum);

    void subscribeTopic(const std::string &forum, const std::string &topic);
    void unsubscribeTopic(const std::string &forum, const std::string &topic);

    std::string getStatus();

// clang-format off
logos_events:
    // Re-emitted from forum_comms.postReceived — UI backend subscribes here.
    void postReceived(const std::string &forum,
                      const std::string &topic,
                      const std::string &content,
                      const std::string &author_id);

    void statusChanged(const std::string &status);
// clang-format on

private:
    std::string status_{"initialising"};

    void setStatus(const std::string &s);
};
