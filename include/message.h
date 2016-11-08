//
// Copyright (C) Michael Yang. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//

#pragma once

#include <experimental/optional>
#include <string>
#include <vector>

namespace ohmyarch {
class update;

class chat {
  public:
    chat(chat &&other) noexcept : id_(other.id_) {}

    int64_t id() const { return id_; }

    friend class message;
    friend std::experimental::optional<std::vector<update>> get_updates();

  private:
    chat() {}

    int64_t id_;
};

class message_entity {
  public:
    message_entity(message_entity &&other) noexcept
        : type_(std::move(other.type_)), offset_(other.offset_),
          length_(other.length_) {}
    message_entity(const std::string &type, std::int32_t offset,
                   std::int32_t length)
        : type_(type), offset_(offset), length_(length) {}

    const std::string &type() const { return type_; }
    std::int32_t offset() const { return offset_; }
    std::int32_t length() const { return length_; }

  private:
    std::string type_;
    std::int32_t offset_;
    std::int32_t length_;
};

class message {
  public:
    message(message &&other) noexcept
        : chat_(std::move(other.chat_)), text_(std::move(other.text_)),
          entities_(std::move(other.entities_)) {}

    const class chat &chat() const { return chat_; }
    const std::experimental::optional<std::string> &text() const {
        return text_;
    }
    const std::experimental::optional<std::vector<message_entity>> &
    entities() const {
        return entities_;
    }

    friend std::experimental::optional<std::vector<update>> get_updates();

  private:
    message() {}

    class chat chat_;
    std::experimental::optional<std::string> text_;
    std::experimental::optional<std::vector<message_entity>> entities_;
};

class update {
  public:
    update(update &&other) noexcept
        : update_id_(other.update_id_), message_(std::move(other.message_)) {}

    int32_t update_id() const { return update_id_; }
    const std::experimental::optional<class message> &message() const {
        return message_;
    }

    friend std::experimental::optional<std::vector<update>> get_updates();

  private:
    update() {}

    int32_t update_id_;
    std::experimental::optional<class message> message_;
};

std::experimental::optional<std::string> get_me();

std::experimental::optional<std::vector<update>> get_updates();

void send_message(int64_t chat_id, const std::string &text);

void send_document(int64_t chat_id, const std::string &uri);
}