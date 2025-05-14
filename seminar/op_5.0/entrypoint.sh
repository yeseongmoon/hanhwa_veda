#!/bin/bash

TEAM_USERS=("jaehyung" "dabeen" "ong" "yeseong")
PASSWORD="1234"

for user in "${TEAM_USERS[@]}"; do
  id -u "$user" &>/dev/null || useradd -m "$user"
  echo "$user:$PASSWORD" | chpasswd
done

echo "✅ Team accounts created: ${TEAM_USERS[*]}"
echo "Password for all accounts: $PASSWORD"

exec /usr/sbin/sshd -D
