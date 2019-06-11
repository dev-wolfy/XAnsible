#include "newtaskform.h"
#include "ui_newtaskform.h"

newTaskForm::newTaskForm(QWidget *parent, QList<tabPageEdit*> *EditList) :
    QDialog(parent),
    ui(new Ui::newTaskForm)
{
    Q_INIT_RESOURCE(ressources);

    ui->setupUi(this);
    ui->moduleExplainFrame->setOpenExternalLinks(true);

    this->showMaximized();

    setUpModuleFamily();

    connect(ui->moduleFamily, &QComboBox::currentTextChanged, this, &newTaskForm::setUpModuleName);
    connect(ui->moduleName, &QComboBox::currentTextChanged, this, &newTaskForm::setUpDescription);

    this->ptr_EditList = EditList;

}

void newTaskForm::setUpModuleFamily()
{
    ui->moduleFamily->addItem("Cloud modules");
    ui->moduleFamily->addItem("Clustering modules");
    ui->moduleFamily->addItem("Commands modules");
    ui->moduleFamily->addItem("Crypto modules");
    ui->moduleFamily->addItem("Databases modules");
    ui->moduleFamily->addItem("Files modules");
    ui->moduleFamily->addItem("Identity modules");
    ui->moduleFamily->addItem("Inventory modules");
    ui->moduleFamily->addItem("Messaging modules");
    ui->moduleFamily->addItem("Monitoring modules");
    ui->moduleFamily->addItem("Net Tools modules");
    ui->moduleFamily->addItem("Network modules");
    ui->moduleFamily->addItem("Notification modules");
    ui->moduleFamily->addItem("Packaging modules");
    ui->moduleFamily->addItem("Remote Management modules");
    ui->moduleFamily->addItem("Source Control modules");
    ui->moduleFamily->addItem("Storage modules");
    ui->moduleFamily->addItem("System modules");
    ui->moduleFamily->addItem("Utilities modules");
    ui->moduleFamily->addItem("Web Infrastructure modules");
    ui->moduleFamily->addItem("Windows modules");

    ui->moduleName->addItem("");
}

void newTaskForm::setUpModuleName()
{
    QString currentFamilyModule = ui->moduleFamily->currentText();

    ui->moduleName->clear();

    if (currentFamilyModule == "Cloud modules") {
        ui->moduleName->addItem("");
    } else if (currentFamilyModule == "Clustering modules") {
        ui->moduleName->addItem("consul");
        ui->moduleName->addItem("consul_acl");
        ui->moduleName->addItem("consul_kv");
        ui->moduleName->addItem("consul_session");
        ui->moduleName->addItem("etcd3");
        ui->moduleName->addItem("pacemaker_cluster");
        ui->moduleName->addItem("znode");
        ui->moduleName->insertSeparator(7);
        ui->moduleName->addItem("k8s");
        ui->moduleName->addItem("k8s_auth");
        ui->moduleName->addItem("k8s_facts");
        ui->moduleName->addItem("k8s_scale");
        ui->moduleName->addItem("k8s_service");
        ui->moduleName->addItem("kubernetes");
        ui->moduleName->insertSeparator(13);
        ui->moduleName->addItem("oc");

    } else if (currentFamilyModule == "Commands modules") {
        ui->moduleName->addItem("command");
        ui->moduleName->setCurrentIndex(0);
        ui->moduleName->addItem("expect");
        ui->moduleName->addItem("psexec");
        ui->moduleName->addItem("raw");
        ui->moduleName->addItem("script");
        ui->moduleName->addItem("shell");
        ui->moduleName->addItem("telnet");

    } else if (currentFamilyModule == "Crypto modules") {
        ui->moduleName->addItem("certificate_complete_chain");
        ui->moduleName->addItem("get_certificate");
        ui->moduleName->addItem("luks_device");
        ui->moduleName->addItem("openssh_cert");
        ui->moduleName->addItem("openssh_keypair");
        ui->moduleName->addItem("openssl_certificate");
        ui->moduleName->addItem("openssl_certificate_info");
        ui->moduleName->addItem("openssl_csr");
        ui->moduleName->addItem("openssl_csr_info");
        ui->moduleName->addItem("openssl_dhparam");
        ui->moduleName->addItem("openssl_pkcs12");
        ui->moduleName->addItem("openssl_privatekey");
        ui->moduleName->addItem("openssl_privatekey_info");
        ui->moduleName->addItem("openssl_publickey");
        ui->moduleName->insertSeparator(14);
        ui->moduleName->addItem("acme_account");
        ui->moduleName->addItem("acme_account_info");
        ui->moduleName->addItem("acme_certificate");
        ui->moduleName->addItem("acme_certificate_revoke");
        ui->moduleName->addItem("acme_challenge_cert_helper");
        ui->moduleName->addItem("acme_inspect");

    } else if (currentFamilyModule == "Databases modules") {
        ui->moduleName->addItem("mongodb_parameter");
        ui->moduleName->addItem("mongodb_replicaset");
        ui->moduleName->addItem("mongodb_shard");
        ui->moduleName->addItem("mongodb_user");
        ui->moduleName->insertSeparator(4);
        ui->moduleName->addItem("mysql_db");
        ui->moduleName->addItem("mysql_replication");
        ui->moduleName->addItem("mysql_user");
        ui->moduleName->addItem("mysql_variables");

    } else if (currentFamilyModule == "Files modules") {
        ui->moduleName->addItem("acl");
        ui->moduleName->addItem("archive");
        ui->moduleName->addItem("assemble");
        ui->moduleName->addItem("blockinfile");
        ui->moduleName->addItem("copy");
        ui->moduleName->addItem("fetch");
        ui->moduleName->addItem("file");
        ui->moduleName->addItem("find");
        ui->moduleName->addItem("ini_file");
        ui->moduleName->addItem("iso_extract");
        ui->moduleName->addItem("lineinfile");
        ui->moduleName->addItem("patch");
        ui->moduleName->addItem("read_csv");
        ui->moduleName->addItem("replace");
        ui->moduleName->addItem("stat");
        ui->moduleName->addItem("synchronize");
        ui->moduleName->addItem("tempfile");
        ui->moduleName->addItem("template");
        ui->moduleName->addItem("unarchive");
        ui->moduleName->addItem("xattr");
        ui->moduleName->addItem("xml");

    } else if (currentFamilyModule == "Identity modules") {
        ui->moduleName->addItem("onepassword_facts");
        ui->moduleName->insertSeparator(1);
        ui->moduleName->addItem("cyberark_authentication");
        ui->moduleName->addItem("cyberark_user");
        ui->moduleName->insertSeparator(3);
        ui->moduleName->addItem("ipa_config");
        ui->moduleName->addItem("ipa_dnsrecord");
        ui->moduleName->addItem("ipa_dnszone");
        ui->moduleName->addItem("ipa_group");
        ui->moduleName->addItem("ipa_hbacrule");
        ui->moduleName->addItem("ipa_host");
        ui->moduleName->addItem("ipa_hostgroup");
        ui->moduleName->addItem("ipa_role");
        ui->moduleName->addItem("ipa_service");
        ui->moduleName->addItem("ipa_subca");
        ui->moduleName->addItem("ipa_sudocmd");
        ui->moduleName->addItem("ipa_sudocmdgroup");
        ui->moduleName->addItem("ipa_sudorule");
        ui->moduleName->addItem("ipa_user");
        ui->moduleName->addItem("ipa_vault");
        ui->moduleName->insertSeparator(18);
        ui->moduleName->addItem("keycloak_client");
        ui->moduleName->addItem("keycloak_clienttemplate");
        ui->moduleName->addItem("keycloak_group");
        ui->moduleName->insertSeparator(21);
        ui->moduleName->addItem("opendj_backendprop");

    } else if (currentFamilyModule == "Inventory modules") {
        ui->moduleName->addItem("add_host");
        ui->moduleName->addItem("group_by");

    } else if (currentFamilyModule == "Messaging modules") {
        ui->moduleName->addItem("rabbitmq_binding");
        ui->moduleName->addItem("rabbitmq_exchange");
        ui->moduleName->addItem("rabbitmq_global_parameter");
        ui->moduleName->addItem("rabbitmq_parameter");
        ui->moduleName->addItem("rabbitmq_plugin");
        ui->moduleName->addItem("rabbitmq_policy");
        ui->moduleName->addItem("rabbitmq_queue");
        ui->moduleName->addItem("rabbitmq_user");
        ui->moduleName->addItem("rabbitmq_vhost");
        ui->moduleName->addItem("rabbitmq_vhost_limits");
    } else if (currentFamilyModule == "Monitoring modules") {

    } else if (currentFamilyModule == "Net Tools modules") {

    } else if (currentFamilyModule == "Network modules") {

    } else if (currentFamilyModule == "Notification modules") {

    } else if (currentFamilyModule == "Packaging modules") {
        ui->moduleName->addItem("bower");
        ui->moduleName->addItem("bundler");
        ui->moduleName->addItem("composer");
        ui->moduleName->addItem("cpanm");
        ui->moduleName->addItem("easy_install");
        ui->moduleName->addItem("gem");
        ui->moduleName->addItem("maven_artifact");
        ui->moduleName->addItem("npm");
        ui->moduleName->addItem("pear");
        ui->moduleName->addItem("pip");
        ui->moduleName->addItem("pip_package_info");
        ui->moduleName->addItem("yarn");
        ui->moduleName->insertSeparator(12);
        ui->moduleName->addItem("apk");
        ui->moduleName->addItem("apt");
        ui->moduleName->addItem("apt_key");
        ui->moduleName->addItem("apt_repo");
        ui->moduleName->addItem("apt_repository");
        ui->moduleName->addItem("apt_rpm");
        ui->moduleName->addItem("dnf");
        ui->moduleName->addItem("dpkg_selections");
        ui->moduleName->addItem("flatpak");
        ui->moduleName->addItem("flatpak_remote");
        ui->moduleName->addItem("homebrew");
        ui->moduleName->addItem("homebrew_cask");
        ui->moduleName->addItem("homebrew_tap");
        ui->moduleName->addItem("installp");
        ui->moduleName->addItem("layman");
        ui->moduleName->addItem("macports");
        ui->moduleName->addItem("openbsd_pkg");
        ui->moduleName->addItem("opkg");
        ui->moduleName->addItem("package");
        ui->moduleName->addItem("package_facts");
        ui->moduleName->addItem("pacman");
        ui->moduleName->addItem("pkg5");
        ui->moduleName->addItem("pkg5_publisher");
        ui->moduleName->addItem("pkgin");
        ui->moduleName->addItem("pkgng");
        ui->moduleName->addItem("pkgutil");
        ui->moduleName->addItem("portage");
        ui->moduleName->addItem("portinstall");
        ui->moduleName->addItem("pulp_repo");
        ui->moduleName->addItem("redhat_subscription");
        ui->moduleName->addItem("rhn_channel");
        ui->moduleName->addItem("rhn_register");
        ui->moduleName->addItem("rhsm_release");
        ui->moduleName->addItem("rhsm_repository");
        ui->moduleName->addItem("rpm_key");
        ui->moduleName->addItem("slackpkg");
        ui->moduleName->addItem("snap");
        ui->moduleName->addItem("sorcery");
        ui->moduleName->addItem("svr4pkg");
        ui->moduleName->addItem("swdepot");
        ui->moduleName->addItem("swupd");
        ui->moduleName->addItem("urpmi");
        ui->moduleName->addItem("xbps");
        ui->moduleName->addItem("yum");
        ui->moduleName->addItem("yum_repository");
        ui->moduleName->addItem("zypper");
        ui->moduleName->addItem("zypper_repository");

    } else if (currentFamilyModule == "Remote Management modules") {

    } else if (currentFamilyModule == "Source Control modules") {
        ui->moduleName->addItem("bzr");
        ui->moduleName->addItem("git");
        ui->moduleName->addItem("git_config");
        ui->moduleName->addItem("github_deploy_key");
        ui->moduleName->addItem("github_hooks");
        ui->moduleName->addItem("github_issue");
        ui->moduleName->addItem("github_key");
        ui->moduleName->addItem("github_release");
        ui->moduleName->addItem("github_webhook");
        ui->moduleName->addItem("github_webhook_facts");
        ui->moduleName->addItem("gitlab_deploy_key");
        ui->moduleName->addItem("gitlab_group");
        ui->moduleName->addItem("gitlab_hook");
        ui->moduleName->addItem("gitlab_project");
        ui->moduleName->addItem("gitlab_runner");
        ui->moduleName->addItem("gitlab_user");
        ui->moduleName->addItem("hg");
        ui->moduleName->addItem("subversion");
        ui->moduleName->insertSeparator(18);
        ui->moduleName->addItem("bitbucket_access_key");
        ui->moduleName->addItem("bitbucket_pipeline_key_pair");
        ui->moduleName->addItem("bitbucket_pipeline_known_host");
        ui->moduleName->addItem("bitbucket_pipeline_variable");

    } else if (currentFamilyModule == "Storage modules") {

    } else if (currentFamilyModule == "System modules") {

    } else if (currentFamilyModule == "Utilities modules") {
        ui->moduleName->addItem("meta");
        ui->moduleName->insertSeparator(1);
        ui->moduleName->addItem("assert");
        ui->moduleName->addItem("async_status");
        ui->moduleName->addItem("debug");
        ui->moduleName->addItem("fail");
        ui->moduleName->addItem("import_playbook");
        ui->moduleName->addItem("import_role");
        ui->moduleName->addItem("import_tasks");
        ui->moduleName->addItem("include");
        ui->moduleName->addItem("include_role");
        ui->moduleName->addItem("include_tasks");
        ui->moduleName->addItem("include_vars");
        ui->moduleName->addItem("pause");
        ui->moduleName->addItem("set_fact");
        ui->moduleName->addItem("set_stats");
        ui->moduleName->addItem("wait_for");
        ui->moduleName->addItem("wait_for_connection");

    } else if (currentFamilyModule == "Web Infrastructure modules") {

    } else if (currentFamilyModule == "Windows modules") {

    } else {
        ui->moduleName->addItem("Pas de module");
    }
}

void newTaskForm::setUpDescription()
{
    QString currentFamilyModule = ui->moduleFamily->currentText();
    QString currentModuleName = ui->moduleName->currentText();

    QString fileName;
    QTextDocument fileContent;

    if (!currentFamilyModule.isNull() || !currentFamilyModule.isEmpty()) {
        if (!currentModuleName.isNull() || !currentFamilyModule.isEmpty()) {

            fileName = ":/html/html/" + currentModuleName + ".html";

            if (!fileName.isNull() || !fileName.isEmpty()) {
                QFile htmlSource(fileName);

                if (htmlSource.open(QFile::ReadOnly | QFile::Text)) {
                    fileContent.setHtml(htmlSource.readAll());
                    ui->moduleExplainFrame->setHtml(fileContent.toHtml());
                    htmlSource.close();
                }
            }

        }
    }
}

void newTaskForm::setUpTaskScript()
{
    QString currentFamilyModule = ui->moduleFamily->currentText();
    QString currentModuleName = ui->moduleName->currentText();

    QString fileName;
    QTextDocument fileContent;

    if (!currentFamilyModule.isNull() || !currentFamilyModule.isEmpty()) {
        if (!currentModuleName.isNull() || !currentFamilyModule.isEmpty()) {

            fileName = ":/html/html/" + currentModuleName + ".xatemplate";

            if (!fileName.isNull() || !fileName.isEmpty()) {
                QFile htmlSource(fileName);

                if (htmlSource.open(QFile::ReadOnly | QFile::Text)) {
                    fileContent.setHtml(htmlSource.readAll());
                    ui->moduleExplainFrame->setHtml(fileContent.toHtml());
                    htmlSource.close();
                }
            }

        }
    }
}

QString newTaskForm::formatHtmlSourceCode(const QString &sourceToInsert)
{
    QString completeSourceCode = sourceToInsert;
    return completeSourceCode;
}

/*QAbstractItemModel *newTaskForm::modelFromFile(const QString &fileName)
{
    QFile file(fileName);
    QString line;
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return new QStringListModel(this->completer);
    }

    QStringList words;
    while (!file.atEnd()) {
        line = file.readLine();
        if (!line.isEmpty()) {
            words.append(line);
        }
    }

    QStandardItemModel *m = new QStandardItemModel(words.count(), 1, this->completer);
    for (int i = 0; i < words.count(); ++i) {
        QModelIndex name = m->index(i, 0);
        m->setData("", name);
    }

    return m;
}*/

newTaskForm::~newTaskForm()
{
    delete ui;
}

QString newTaskForm::getTaskName() const
{
    return taskName;
}

void newTaskForm::setTaskName(const QString &value)
{
    taskName = value;
}
