#include "forum_app_impl.h"
#include "logos_sdk.h"

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
