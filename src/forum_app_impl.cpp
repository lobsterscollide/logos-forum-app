#include "forum_app_impl.h"
#include "logos_sdk.h"

// TODO: subscribe to forum_comms.postReceived during initialisation so incoming
// posts are forwarded upward to the UI backend. The exact subscription API
// depends on the logos-delivery SDK. Expected shape:
//
//   modules().forum_comms.onPostReceived([this](const std::string &topic,
//                                               const std::string &content,
//                                               const std::string &sender_id) {
//       postReceived(topic, content, sender_id);
//   });
//
// Similarly, subscribe to forum_comms.identityReady to surface the local
// node identity to the UI:
//
//   modules().forum_comms.onIdentityReady([this](const std::string &identity) {
//       (void)identity; // notify UI via statusChanged or a dedicated event
//   });

void ForumAppImpl::publishPost(const std::string &topic, const std::string &content)
{
    const std::string identity = modules().forum_comms.getIdentity();
    modules().forum_comms.publishPost(topic, content, identity);
}

void ForumAppImpl::subscribeTopic(const std::string &topic)
{
    modules().forum_comms.subscribeTopic(topic);
    setStatus("subscribed: " + topic);
}

void ForumAppImpl::unsubscribeTopic(const std::string &topic)
{
    modules().forum_comms.unsubscribeTopic(topic);
    setStatus("unsubscribed: " + topic);
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
