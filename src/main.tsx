import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import { App } from './presentation/App'
import './presentation/styles.css'
import './presentation/auth-3d.css'

createRoot(document.getElementById('root')!).render(
  <StrictMode>
    <App />
  </StrictMode>,
)
