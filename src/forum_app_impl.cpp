#include "forum_app_impl.h"
#include "logos_sdk.h"

// TODO: subscribe to forum_comms events during initialisation so incoming
// posts are forwarded upward to the UI backend. Expected shape:
//
//   modules().forum_comms.onPostReceived([this](
//       const std::string &forum, const std::string &topic,
//       const std::string &content, const std::string &author_id) {
//       postReceived(forum, topic, content, author_id);
//   });
//
//   modules().forum_comms.onIdentityReady([this](const std::string &identity) {
//       setStatus("identity ready: " + identity);
//   });

ForumAppImpl::ForumAppImpl()
{
    // V1: auto-subscribe to the default forum on startup.
    subscribeToForum("Logos Forum");
}

void ForumAppImpl::publishPost(const std::string &forum,
                               const std::string &topic,
                               const std::string &content)
{
    // author_id is the sender's public key; empty string until logos-delivery
    // assigns a local identity via forum_comms.getIdentity().
    const std::string author_id = modules().forum_comms.getIdentity();
    (void)modules().forum_comms.publishPost(forum, topic, content, author_id);
}

void ForumAppImpl::subscribeToForum(const std::string &forum)
{
    (void)modules().forum_comms.subscribeToForum(forum);
    setStatus("subscribed to forum: " + forum);
}

void ForumAppImpl::unsubscribeFromForum(const std::string &forum)
{
    (void)modules().forum_comms.unsubscribeFromForum(forum);
    setStatus("unsubscribed from forum: " + forum);
}

void ForumAppImpl::subscribeTopic(const std::string &forum, const std::string &topic)
{
    (void)modules().forum_comms.subscribeTopic(forum, topic);
    setStatus("subscribed to topic: " + forum + " › " + topic);
}

void ForumAppImpl::unsubscribeTopic(const std::string &forum, const std::string &topic)
{
    (void)modules().forum_comms.unsubscribeTopic(forum, topic);
    setStatus("unsubscribed from topic: " + forum + " › " + topic);
}

std::string ForumAppImpl::getStatus()
{
    return status_;
}

void ForumAppImpl::setStatus(const std::string &s)
{
    status_ = s;
    statusChanged(s);
}
