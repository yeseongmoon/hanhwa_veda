FROM wop:5.00

RUN apt-get update && apt-get install -y openssh-server sudo && \
    mkdir /var/run/sshd && \
    useradd -m -s /bin/bash jaehyung && echo "jaehyung:1234" | chpasswd && usermod -aG sudo jaehyung && \
    useradd -m -s /bin/bash dabeen && echo "dabeen:1234" | chpasswd && usermod -aG sudo dabeen && \
    useradd -m -s /bin/bash ong && echo "ong:1234" | chpasswd && usermod -aG sudo ong && \
    useradd -m -s /bin/bash yeseong && echo "yeseong:1234" | chpasswd && usermod -aG sudo yeseong && \
    echo "%sudo ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

EXPOSE 22
CMD ["/usr/sbin/sshd", "-D"]

ENTRYPOINT ["/entrypoint.sh"]
