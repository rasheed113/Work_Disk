export type NavigationButtonKind =
  | 'BACK'
  | 'PAGE'
  | 'MORE'
  | 'CLOSE'
  | 'FORWARD'
  | 'HOME'
  | 'MENU'

export interface NavigationButton {
  readonly id: string
  readonly kind: NavigationButtonKind
  readonly label: string
  readonly destination?: string
}

export interface NavigationButtonContext {
  readonly registeredDestinations: ReadonlySet<string>
  readonly availableCapabilities: ReadonlySet<string>
}

export class NavigationButtonsBot {
  getButtons(context: NavigationButtonContext): readonly NavigationButton[] {
    const buttons: NavigationButton[] = [
      { id: 'nav-back', kind: 'BACK', label: 'Back' },
      { id: 'nav-more', kind: 'MORE', label: 'More' },
      { id: 'nav-close', kind: 'CLOSE', label: 'Close' },
      { id: 'nav-forward', kind: 'FORWARD', label: 'Forward' },
    ]

    if (context.registeredDestinations.has('/dashboard')) {
      buttons.push({
        id: 'nav-home',
        kind: 'HOME',
        label: 'Home',
        destination: '/dashboard',
      })
    }

    for (const destination of context.registeredDestinations) {
      if (destination === '/dashboard') continue
      buttons.push({
        id: `nav-page-${destination.replace(/[^a-z0-9]+/gi, '-')}`,
        kind: 'PAGE',
        label: destination,
        destination,
      })
    }

    return buttons
  }
}
