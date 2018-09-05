#pragma once

#include <Core/core_global.h>

#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include <QtCore/QMutex>
#include <QtCore/QVariantMap>

namespace P1 {
  namespace Core {

    class CORE_EXPORT Marketing : public QObject
    {
      Q_OBJECT
      Q_ENUMS(MarketingTarget)
      Q_FLAGS(MarketingTargets)
      Q_ENUMS(InstallerStep)
      Q_FLAGS(InstallerSteps)
    public:

      enum MarketingTarget {
        FirstRunLauncher = 2596, // Первый запуск Launcher
        StartDownloadService = 37, // Начало загрузки игры
        FinishDownloadService = 38, // Окончание загрузки игры
        FinishInstallService = 39, // Инсталляция игры
        FirstRunService = 40, // Первый вход в игру
        SuccessAuthInGN = 2633, // Авторизация в Launcher
        TooLongInstallTime = 2650, // Слишком долгая установка/закачака сервиса.
        ErrorDuringInstall = 2651, // Ошибка входе установки/закачки сервиса.
        CloseService = 2660, // Завершение работы игры.
        SendDownloadServiceInfo = 2661, // Информация о закачке игры.
        StartService = 2662, // Запуск игры.
        ClickOnMainButton = 2663, // Клик по кнопке запустить игру.
        NewGameServerShowed = 2694, // Уведомление об открытии нового сервера
        ClickNewGameServerPlay = 2695, // Нажали кнопку "Играть" на новом сервере
        InstalledWasNotRunShowed = 2696, // Уведомление, напоминающее о том, что ты скачал, но еще ни разу не входил в игру
        ClickInstalledWasNotRunPlay = 2697, // Нажали кнопку "Играть" на уведомлении, напоминающем о том, что ты скачал, но еще ни разу не входил в игру
        AfterGameAdvertisingAction = 2701, // Произвели действие с окном AfterGameAdvertising
        AuthByOldGnaInfo = 2720, // авторизация под данным из гна генерал
        GuestAccountRequest = 2721, // создание гстевого аккаунта
        GuestAccountConfirm = 2722, // подтвеждение гостевого акк
        AnnouncementShown = 2723, // показали любой анонс или надпоминание
        AnnouncementClosedClicked = 2726, // в анонсе или надпоминании тыкнули в кнопку закрыть
        AnnouncementMissClicked = 2725, // в анонсе или надпоминании тыкнули вне кнопок
        AnnouncementActionClicked = 2724, // в анонсе или надпоминании тыкнули в кнопку действия
        AnyStartLauncher = 2731, // Любой запуск Launcher.
        ProblemAfterGameStart = 2748, // Проблемы при запуске игры
        NotLikeTheGame = 2749, // Игра не понравилась - пользователь играл слишком мало
        ServiceUninstalledFromOS = 2762,  // Игра удалена с помощью средств ОС (Панель Управления->Программы и компоненты)
        ServiceUninstalledFromUI = 2763, // Игра удалена с помощью нажатия кнопки "Удалить" в настройках
        ApplicationSettingsChanged = 2768, // Информация о выбранных настройках приложения.
        FirstStartDownloadService = 2795, // Первое начало скачивание сервиса. Посылается один раз на событие.
      };

      Q_DECLARE_FLAGS(P1::Core::Marketing::MarketingTargets, P1::Core::Marketing::MarketingTarget)

      enum InstallerStep {
        InstallAcceptLicense = 2608
      };

      Q_DECLARE_FLAGS(P1::Core::Marketing::InstallerSteps, P1::Core::Marketing::InstallerStep)

      static Marketing *instance();

      static void send(MarketingTargets target);
      static void send(MarketingTargets target, const QString& serviceId);
      static void send(MarketingTargets target, const QVariantMap& params);

      /*!
        \fn static void Marketing::send(MarketingTargets target, const QString& serviceId,
          const QVariantMap& params);
        \brief Генерирует событие на отправку маркетингово шага.
        \author Ilya.Tkachenko
        \date 30.07.2012
        \param target    Маркетинговая цель.
        \param serviceId Идентификатор сервиса. Если его нету, то следует указать "0" или воспользоваться 
                         перегруженными методами.
        \param params    Дополнительные параметры.
      */
      static void send(MarketingTargets target, const QString& serviceId, const QVariantMap& params);


      /*!
        \fn static void Marketing::sendOnceByService(MarketingTargets target, const QString& serviceId);
        \brief Метод аналогичный send, но подразумевается, что указанная маркетинговая цель будет послана
               один раз для каждого сервиса. Это обеспечивает непосредственно обработчик события 
               sendOnceByServiceMarketingRequest в самом приложении.
        \author Ilya.Tkachenko
        \date 30.07.2012
        \param target    Маркетинговая цель.
        \param serviceId Идентификатор сервиса. Так как ключь отправленности сохраняется по каждому сервису, 
                         этот параметр является обязательным.
      */
      static void sendOnceByService(MarketingTargets target, const QString& serviceId);
      static void sendOnceByService(MarketingTargets target, const QString& serviceId, const QVariantMap& params);

      static void sendOnce(MarketingTargets target);
      static void sendOnce(MarketingTargets target, const QString& serviceId);
      static void sendOnce(MarketingTargets target, const QVariantMap& params);

      /*!
        \fn static void Marketing::sendOnce(MarketingTargets target, const QString& serviceId,
          const QVariantMap& params);
        \brief Метод аналогичный send, но подразумевается, что указанная маркетинговая цель будет послана
               один раз на все приложение. Это обеспечивает непосредственно обработчик события 
               sendOnceMarketingRequest в самом приложении.
        \author Ilya.Tkachenko
        \date 30.07.2012
        \param target    Маркетинговая цель.
        \param serviceId Идентификатор сервиса. Если его нету, то следует указать "0" или воспользоваться 
                         перегруженными методами.
        \param params    Дополнительные параметры.
      */
      static void sendOnce(MarketingTargets target, const QString& serviceId, const QVariantMap& params);


      /*!
        \fn static void Marketing::sendInstallerStepOnce(InstallerSteps step, const QVariantMap& params);
        \brief Sends an installer step once.
        \author Ilya.Tkachenko
        \date 22.01.2013
        \param step   Amount to increment by.
        \param params Options for controlling the operation.
      */
      static void sendInstallerStepOnce(InstallerSteps step, const QVariantMap& params);
      static void sendInstallerStepOnce(InstallerSteps step);

    signals:
      void marketingRequest(P1::Core::Marketing::MarketingTargets target, const QString& serviceId, const QVariantMap& params);
      void sendOnceByServiceMarketingRequest(P1::Core::Marketing::MarketingTargets target, const QString& serviceId, const QVariantMap& params);
      void sendOnceMarketingRequest(P1::Core::Marketing::MarketingTargets target, const QString& serviceId, const QVariantMap& params);

      void sendOnceInstallerStep(P1::Core::Marketing::InstallerSteps target, const QVariantMap& params);

    protected:
      Marketing(QObject* parent = 0);
      ~Marketing();

    private:
      static Marketing *_instance;
      static QMutex _mutex;
      static QString _nullId;
    };
  }
}

Q_DECLARE_METATYPE(P1::Core::Marketing::MarketingTargets);
Q_DECLARE_METATYPE(P1::Core::Marketing::InstallerSteps);
