Name:       harbour-sailmidi

Summary:    MIDI controller for Sailfish OS
Version:    0
Release:    1
License:    LICENSE
URL:        http://example.org/
Source0:    %{name}-%{version}.tar.bz2
Requires:   sailfishsilica-qt5 >= 0.10.9
BuildRequires:  pkgconfig(sailfishapp) >= 1.0.2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(alsa)
BuildRequires:  desktop-file-utils
BuildRequires:  cmake

%description
MIDI controller for Sailfish OS

%package devel
Summary:    Development files for sailmidi

%description devel
%{summary}.

%prep
%setup -q -n %{name}-%{version}

%build

%cmake

%make_build


%install
%make_install

desktop-file-install --delete-original       \
  --dir %{buildroot}%{_datadir}/applications             \
   %{buildroot}%{_datadir}/applications/*.desktop

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png

%files devel
%defattr(-,root,root,-)
%dir %{_includedir}/rtmidi
%{_includedir}/rtmidi/*.h
%{_libdir}/pkgconfig/rtmidi.pc
%dir %{_datadir}/rtmidi
%{_datadir}/rtmidi/*.cmake
