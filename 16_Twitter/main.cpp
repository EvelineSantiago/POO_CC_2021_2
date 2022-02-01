#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>
#include <set>

class Message {
    int id;
    std::string username;
    std::string msg;
    std::set<std::string> likes;

public:
    Message(int id, std::string username, std::string msg) : id{id}, username{username}, msg{msg} {}
    
    int get_id() const {
        return this->id;
    }

    void like(std::string username) {
        likes.insert(username);
    }

    friend std::ostream& operator<<(std::ostream& os, const Message& msg) {
        os << msg.get_id() << ":" << msg.username << " (" << msg.msg << ")";
        if (msg.likes.size() > 0) {
            os << " [";
            bool flag = true;
            for (auto like : msg.likes) {
                if (flag) {
                    os << like;
                    flag = false;
                } else {
                    os << ", " << like;
                }
            }
            os << "]";
        }
        return os;
    }
};

class Inbox {
    std::map<int, Message*> unread;
    std::map<int, Message*> readed;

public:
    Inbox() {}

    std::vector<Message*> get_unread() {
        std::vector<Message*> unreadMsgs;
        for (auto msg : this->unread) {
            unreadMsgs.push_back(msg.second);
        }
        return unreadMsgs;
    }

    std::vector<Message*> get_readed() {
        std::vector<Message*> readedMsgs;
        for (auto msg : this->readed) {
            readedMsgs.push_back(msg.second);
        }
        return readedMsgs;
    }

    Message* get_tweet(int id) {
        auto it = readed.find(id);
        if (it != readed.end()) {
            return it->second;
        } else {
            throw std::runtime_error("fail: tweet nao existe");
        }
    }

    void store_unread(Message* tweet) {
        this->unread[tweet->get_id()] = tweet;
        this->readed[tweet->get_id()] = tweet;
    }

    void store_readed(Message* tweet) {
        this->readed[tweet->get_id()] = tweet;
    }

    friend std::ostream& operator<<(std::ostream& os, Inbox& inbox) {
        for (auto msg : inbox.get_readed()) {
            os << *msg << "\n";
        }
        return os;
    }
};

class User {
    std::string username;
    Inbox inbox;
    std::map<std::string, User*> followers;
    std::map<std::string, User*> following;

public:
    User(std::string username) : username{username} {}

    void follow(User* other) {
        auto it = following.find(other->username);
        if (it != following.end()) {
            throw std::runtime_error("fail: ja segue esse usuario");
        } else {
            following[other->username] = other;
            other->followers[username] = this;
        }
    }

    void unfollow(std::string username) {
        if (following.find(username) == following.end()) {
            throw std::runtime_error("fail: nao segue esse usuario");
        } else {
            auto other = following[username];
            following.erase(username);
            other->followers.erase(this->username);
        }
    }

    void like(int twId) {
        inbox.get_tweet(twId)->like(this->username);
    }

    Inbox& get_inbox() {
        return this->inbox;
    }

    void send_tweet(Message* msg) {
        inbox.store_readed(msg);
        for (auto& follower : this->followers) {
            follower.second->get_inbox().store_unread(msg);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const User& user) {
        os << user.username << "\n";
        os << "  seguidos [";
        bool flag = true;
        for (auto f : user.following) {
            if (flag) {
                os << f.first;
                flag = false;
            } else {
                os << ", " << f.first;
            }
        }
        os << "]\n";

        os << "  seguidores [";
        flag = true;
        for (auto f : user.followers) {
            if (flag) {
                os << f.first;
                flag = false;
            } else {
                os << ", " << f.first;
            }
        }
        os << "]\n";
        return os;
    }
};

class Controller {
    std::map<std::string, std::shared_ptr<User>> users;
    std::map<int, std::shared_ptr<Message>> tweets;
    int next_tweet_id {0};

    std::shared_ptr<Message> create_msg(std::string username, std::string msg) {
        tweets[next_tweet_id] = std::make_shared<Message>(next_tweet_id, username, msg);
        next_tweet_id++;
        return tweets[next_tweet_id - 1];
    }

public:
    Controller() {}

    void add_user(std::string username) {
        auto it = users.find(username);
        if (it == users.end()) {
            users[username] = std::make_shared<User>(username);
        } else {
            throw std::runtime_error("fail: usuario ja existe");
        }
    }

    User* get_user(std::string username) {
        auto it = users.find(username);
        if (it != users.end()) {
            return it->second.get();
        } else {
            throw std::runtime_error("fail: usuario nao existe");
        }
    }

    void send_tweet(std::string username, std::string msg) {
        std::shared_ptr<Message> tweet = create_msg(username, msg);
        get_user(username)->send_tweet(tweet.get());
    }

    friend std::ostream& operator<<(std::ostream& os, Controller& ctrl) {
        for (auto user : ctrl.users) {
            os << *user.second << "\n";
        }
        return os;
    }
};

int main() {
    Controller system;

    while(true) {
        std::string line, cmd;
        std::cin >> cmd;
        getline(std::cin, line);
        std::stringstream ss(line);

        try {
            if (cmd == "end") {
                break;

            } else if (cmd == "add") {
                std::string username;
                ss >> username;
                system.add_user(username);

            } else if (cmd == "show") {
                std::cout << system;

            } else if (cmd == "follow") {
                std::string username, other;
                ss >> username >> other;
                system.get_user(username)->follow(system.get_user(other));

            } else if (cmd == "unfollow") {
                std::string username, other;
                ss >> username >> other;
                system.get_user(username)->unfollow(other);

            } else if (cmd == "twittar") {
                std::string username, msg;
                ss >> username;
                getline(ss, msg);
                msg.erase(0, 1);
                system.send_tweet(username, msg);

            } else if (cmd == "like") {
                std::string username;
                int twId;
                ss >> username >> twId;
                system.get_user(username)->like(twId);

            } else if (cmd == "unread") {
                std::string username;
                ss >> username;
                for (auto m : system.get_user(username)->get_inbox().get_unread()) {
                    std::cout << *m << "\n";
                }

            } else if (cmd == "timeline") {
                std::string username;
                ss >> username;
                std::cout << system.get_user(username)->get_inbox();
                
            } else {
                std::cout << "fail: comando invalido\n";
            }
        } catch (std::exception& e) {
            std::cout << e.what() << "\n";
        }
    }
    return 0;
}